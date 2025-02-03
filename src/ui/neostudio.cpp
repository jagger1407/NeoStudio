#include "neostudio.h"
#include "ui_neostudio.h"

#include "src/ui/menu/characterselectiondialog.h"
#include "src/ui/menu/sectionselectiondialog.h"
#include "src/ui/editors/charparamframe.h"

#define VERSION_STRING "Neo Studio v1.5.0"

NeoStudio::NeoStudio(int argc, char* argv[], QWidget* parent) :
    QMainWindow(parent), ui(new Ui::NeoStudio)
{
    if(argc > 2) return;

    Options::InitOptions();

    ui->setupUi(this);
    this->setWindowTitle(VERSION_STRING);

    editors = (QFrame**)calloc(ui->EditorList->count(), sizeof(QFrame*));

    ResetUiMode();

    this->setWindowIcon(QIcon("./assets/icon.png"));

    ui->EditorList->setEnabled(false);

    if(argc == 2)
    {
        file = argv[1];
        QString fileName = file.split('/')[(file.split('/').length()-1)];
        fileName.truncate(fileName.length()-4);
        ui->FileLbl->setText("Current File: " + fileName);
        if(file.endsWith(".pak"))
            InitPakFile();
        else if(file.endsWith(".dat"))
            InitDatFile();
    }

    Debug::Log("NeoStudio constructed.", Debug::INFO);
}

NeoStudio::~NeoStudio() = default;

void NeoStudio::OpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                        "Open File", "", "Character Files (*.pak);;Parameter Files (*.dat)");
    if(filePath.isEmpty())
    {
        Debug::Log("OpenFile: No file selected.", Debug::WARNING);
        return;
    }

    if(!file.isEmpty()) CloseFile();

    file = filePath;

    QString fileName = file.split('/')[(file.split('/').length()-1)];
    fileName.truncate(fileName.length()-4);
    ui->FileLbl->setText("Current File: " + fileName);

    if(file.toLower().endsWith(".pak"))
    {
        InitPakFile();
    }
    else
    {
        InitDatFile();
    }
    Debug::Log(file + " sucessfully opened.", Debug::INFO);
}

void NeoStudio::SaveFile()
{
    if(file == NULL)
    {
        Debug::Log("SaveFile: No file open.", Debug::ERROR);
        return;
    }
    if(file.toLower().endsWith(".pak"))
    {
        if(editors[EDITOR_PARAMETERS] != NULL) {
            ((CharParamFrame*)editors[EDITOR_PARAMETERS])->UpdatePak();
        }
        pak->SavePak(file);
    }
    else if(file.toLower().endsWith(".dat"))
    {
        if(datIndex >= SECTION_OFFSET_GENERAL && datIndex < SECTION_OFFSET_NEXT) {
            QByteArray* data = ((CharParamFrame*)editors[EDITOR_PARAMETERS])->GetCurrentParameterData();
            FileParse::WriteFile(file, data);
        }
    }
    if(FileParse::DoesFileExist(file))
    {
        Debug::Log("File '" + file + "' saved successfully.", Debug::INFO);
    }
}

void NeoStudio::SaveFileAs()
{
    if(file == NULL)
    {
        Debug::Log("SaveFileAs: No file open.", Debug::ERROR);
        return;
    }

    QString newFile;
    if(file.toLower().endsWith(".pak"))
        newFile = QFileDialog::getSaveFileName(this, "Save File", "", "Character Files (*.pak)");
    else if(file.toLower().endsWith(".dat"))
        newFile = QFileDialog::getSaveFileName(this, "Save File", "", "Parameter Files (*.dat)");
    if(newFile == NULL)
    {
        Debug::Log("SaveFileAs: No file selected.", Debug::WARNING);
        return;
    }

    if(newFile.toLower().endsWith(".pak"))
    {
        if(editors[EDITOR_PARAMETERS] != NULL) {
            ((CharParamFrame*)editors[EDITOR_PARAMETERS])->UpdatePak();
        }
        pak->SavePak(newFile);

    }
    else if(newFile.toLower().endsWith(".dat"))
    {
        if(datIndex >= SECTION_OFFSET_GENERAL && datIndex < SECTION_OFFSET_NEXT) {
            QByteArray* data = ((CharParamFrame*)editors[EDITOR_PARAMETERS])->GetCurrentParameterData();
            FileParse::WriteFile(newFile, data);
        }
    }
    if(FileParse::DoesFileExist(newFile))
    {
        Debug::Log("File '" + newFile + "' saved successfully.", Debug::INFO);
    }
}

void NeoStudio::CloseFile()
{
    if(file == NULL)
    {
        Debug::Log("CloseFile: No file open.", Debug::ERROR);
        return;
    }

    if(editors[EDITOR_PARAMETERS] != NULL) {
        ((CharParamFrame*)editors[EDITOR_PARAMETERS])->CloseFile();
        delete editors[EDITOR_PARAMETERS];
        editors[EDITOR_PARAMETERS] = NULL;
    }
    datIndex = SECTION_OFFSET_INVALID;

    //ui->EditorList->clearSelection();
    ui->EditorList->setEnabled(false);

    file = "";
    ui->FileLbl->setText("Open A Character File...");
    Debug::Log("File closed.", Debug::INFO);
}

void NeoStudio::OpenAbout()
{
    Debug::Log("About page opened.", Debug::INFO);
    AboutWindow().exec();
}
void NeoStudio::OpenOptions()
{
    Debug::Log("Option Dialog opened.", Debug::INFO);
    OptionDialog* optionWindow = new OptionDialog();
    optionWindow->exec();

    ResetUiMode();

    delete optionWindow;
}


void NeoStudio::InitPakFile()
{
    pak = new PakControls(file);
    if(pak->HasFailed())
    {
        Debug::Log(".pak file couldn't be opened. Initiation canceled.", Debug::WARNING);
        return;
    }

    ui->EditorList->setEnabled(true);
    ui->EditorList->setCurrentRow(0);
    SelectedEditorChanged(EDITOR_PARAMETERS);
}

void NeoStudio::InitDatFile()
{
    datIndex = (SectionOffset)(file.split('/')[(file.split('/').length()-1)].split("_")[0].toInt());
    if(datIndex < SECTION_OFFSET_GENERAL || datIndex >= SECTION_OFFSET_NEXT)
    {
        Debug::Log("Invalid .dat file.", Debug::ERROR);
        Debug::Log("datIndex = " + QString::number((int)datIndex), Debug::INFO);
        return;
    }
    dat = FileParse::ReadWholeFile(file);

    ui->EditorList->setCurrentRow(0);
    SelectedEditorChanged(EDITOR_PARAMETERS);
}

void NeoStudio::ExportSection()
{
    if(file.isEmpty())
    {
        Debug::Log("No file opened.", Debug::ERROR);
        return;
    }
    if(file.toLower().endsWith(".dat"))
    {
        Debug::Log("Export isn't supported for .dat files. Using 'SaveAs' instead.", Debug::WARNING);
        SaveFileAs();
        return;
    }


    SectionOffset dataType = SECTION_OFFSET_INVALID;

    EditorType curEditor = (EditorType)(ui->EditorList->currentRow());
    switch(curEditor) {
        case EDITOR_PARAMETERS: {
            CharParamFrame* pf = (CharParamFrame*)editors[curEditor];
            dataType = (SectionOffset)(pf->GetCurrentParameterType() + 17);
            break;
        }
        default:
            dataType = (SectionOffset)0;
            break;
    }

    if(!FileParse::DoesFileExist(g_Options.sectionNameFile))
    {
        Debug::Log("Section Name List (" + g_Options.sectionNameFile + ") doesn't exist.", Debug::ERROR);
        return;
    }
    QStringList sectionNames = FileParse::ReadLines(g_Options.sectionNameFile);

    int section = SectionSelectionDialog::SelectExport(dataType);
    if(section == SectionSelectionDialog::ExportAborted) {
        Debug::Log("Export Aborted.", Debug::WARNING);
        return;
    }

    QString saveDir = QFileDialog::getExistingDirectory(this, "Export file to...", QFileInfo(file).absoluteFilePath());
    if(saveDir.isEmpty())
    {
        Debug::Log("No directory selected.", Debug::ERROR);
        return;
    }

    if(section == SectionSelectionDialog::ExportAll) {
        QString pakName = file.split("/")[file.split('/').length()-1];
        pakName.chop(4);
        for(int i=0;i<sectionNames.count();i++) {
            QByteArray d = pak->GetParamData(i);
            FileParse::WriteFile(saveDir + "/" + sectionNames[i], &d);
        }
    }
    else {
        QByteArray* data = new QByteArray(pak->GetParamData(section));
        FileParse::WriteFile(saveDir + "/" + sectionNames[section], data);
        delete data;

        if(FileParse::DoesFileExist(saveDir + "/" + sectionNames[section]))
        {
            Debug::Log("File '" + sectionNames[section] + "' saved successfully.", Debug::INFO);
        }
    }


}

void NeoStudio::ImportSection()
{

    if(file.isEmpty())
    {
        Debug::Log("No file opened. Only use this option to import parameter sections into .pak files.", Debug::ERROR);
        return;
    }
    else if(!file.toLower().endsWith(".pak"))
    {
        Debug::Log("Opened file isn't a .pak file.", Debug::ERROR);
        return;
    }

    QString datPath = QFileDialog::getOpenFileName(this, "Open Section File", file, "Section File (*.*)");
    if(datPath.isEmpty())
    {
        Debug::Log("No path selected.", Debug::WARNING);
        return;
    }
    QByteArray datData = FileParse::ReadWholeFile(datPath);

    QStringList sections = FileParse::ReadLines(g_Options.sectionNameFile);

    datPath = datPath.split("/")[datPath.split("/").count()-1];
    SectionOffset datType = SECTION_OFFSET_INVALID;

    for(int i=0;i<SECTION_OFFSET_COUNT;i++) {
        if(datPath == sections[i])
            datType = (SectionOffset)i;
    }

    if(datType >= SECTION_OFFSET_GENERAL && datType < SECTION_OFFSET_NEXT) {
        CharParamFrame* pf = (CharParamFrame*)editors[EDITOR_PARAMETERS];
        if(pf != NULL) {
            pf->ImportParameterData((ParameterType)(datType-17), datData);
        }
    }
    pak->UpdateParamData(datType, &datData);
}
void NeoStudio::SelectedEditorChanged(int editorId)
{
    if(file == NULL) {
        return;
    }

    if(editorId < 0) {
        ui->EditorScrollArea->setWidget(NULL);
    }

    if(editors[editorId] == NULL) {
        switch(editorId) {
            case EDITOR_PARAMETERS:
                if(file.toLower().endsWith(".pak"))
                    editors[editorId] = new CharParamFrame(pak);
                else if(file.toLower().endsWith(".dat")) {
                    editors[editorId] = new CharParamFrame((ParameterType)(datIndex - 17), &dat);
                }
                break;
        }
    }

    ui->EditorScrollArea->setWidget(editors[editorId]);
}

void NeoStudio::ResetUiMode()
{
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));

    if(editors[EDITOR_PARAMETERS] != NULL)
        ((CharParamFrame*)editors[EDITOR_PARAMETERS])->ResetUiMode();
}
