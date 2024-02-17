#include "neostudio.h"
#include "ui_neostudio.h"

#include "src/ui/menu/characterselectiondialog.h"

#define VERSION_STRING "Neo Studio v1.1.1"

NeoStudio::NeoStudio(int argc, char* argv[], QWidget* parent) :
    QMainWindow(parent), ui(new Ui::NeoStudio)
{
    if(argc > 2) return;

    Options::InitOptions();

    ui->setupUi(this);
    this->setWindowTitle(VERSION_STRING);
    ui->ParameterTabs->setCurrentIndex(PARAM_TYPE_GENERAL);
    ResetUiMode();

    this->setWindowIcon(QIcon("./assets/icon.png"));

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
    Debug::Log("OpenFile slot triggered.", Debug::INFO);

    QString filePath = QFileDialog::getOpenFileName(this,
                                        "Open File", "", "Character Files (*.pak);;Parameter Files (*.dat)");
    if(filePath.isEmpty())
    {
        Debug::Log("OpenFile: No file selected.", Debug::WARNING);
        return;
    }
    file = filePath;

    QString fileName = file.split('/')[(file.split('/').length()-1)];
    fileName.truncate(fileName.length()-4);
    ui->FileLbl->setText("Current File: " + fileName);

    for(int i=0;i<ui->ParameterTabs->count();i++) ui->ParameterTabs->setTabEnabled(i, true);

    if(file.toLower().endsWith(".pak"))
    {
        InitPakFile();
    }
    else
    {
        InitDatFile();
    }
}

void NeoStudio::SaveFile()
{
    Debug::Log("SaveFile slot triggered.", Debug::INFO);
    if(file == NULL)
    {
        Debug::Log("SaveFile: No file open.", Debug::ERROR);
        return;
    }
    if(file.toLower().endsWith(".pak"))
    {
        pak->UpdateParamData(PARAM_TYPE_GENERAL, generalWindow->gp->GetFileData());
        pak->UpdateParamData(PARAM_TYPE_MELEE, meleeWindow->mp->GetFileData());
        pak->UpdateParamData(PARAM_TYPE_KI_BLAST, kiWindow->kp->GetFileData());
        pak->UpdateParamData(PARAM_TYPE_MOVEMENT, moveWindow->mp->GetFileData());
        pak->SavePak(file);
    }
    else if(file.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case PARAM_TYPE_GENERAL:
                datPtr = generalWindow->gp->GetFileData();
                break;
            case PARAM_TYPE_MELEE:
                datPtr = meleeWindow->mp->GetFileData();
                break;
            case PARAM_TYPE_KI_BLAST:
                datPtr = kiWindow->kp->GetFileData();
                break;
            case PARAM_TYPE_MOVEMENT:
                datPtr = moveWindow->mp->GetFileData();
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR);
                return;
        }
        FileParse::WriteFile(file, datPtr);
    }
}

void NeoStudio::SaveFileAs()
{
    Debug::Log("SaveFileAs slot triggered.", Debug::INFO);
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
        pak->UpdateParamData(PARAM_TYPE_GENERAL, generalWindow->gp->GetFileData());
        pak->UpdateParamData(PARAM_TYPE_MELEE, meleeWindow->mp->GetFileData());
        pak->UpdateParamData(PARAM_TYPE_KI_BLAST, kiWindow->kp->GetFileData());
        pak->UpdateParamData(PARAM_TYPE_MOVEMENT, moveWindow->mp->GetFileData());
        pak->SavePak(newFile);
    }
    else if(newFile.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case PARAM_TYPE_GENERAL:
                datPtr = generalWindow->gp->GetFileData();
                break;
            case PARAM_TYPE_MELEE:
                datPtr = meleeWindow->mp->GetFileData();
                break;
            case PARAM_TYPE_KI_BLAST:
                datPtr = kiWindow->kp->GetFileData();
                break;
            case PARAM_TYPE_MOVEMENT:
                datPtr = moveWindow->mp->GetFileData();
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR);
                return;
        }
        FileParse::WriteFile(newFile, datPtr);
        delete datPtr;
    }
}

void NeoStudio::CloseFile()
{
    if(file == NULL)
    {
        Debug::Log("CloseFile: No file open.", Debug::ERROR);
        return;
    }
    Debug::Log("CloseFile slot triggered.", Debug::INFO);
    if(generalWindow != nullptr)
        generalWindow->close();
    if(meleeWindow != nullptr)
        meleeWindow->close();
    if(kiWindow != nullptr)
        kiWindow->close();
    if(moveWindow != nullptr)
        moveWindow->close();
    file = "";
    ui->FileLbl->setText("Open A Character File...");

    for(int i=0;i<ui->ParameterTabs->count();i++) ui->ParameterTabs->setTabEnabled(i, true);
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
    Debug::Log("InitPakFile called.", Debug::INFO);
    pak = new PakControls(file);
    if(pak->HasFailed()) return;

    if(generalWindow != nullptr) delete generalWindow;
    if(meleeWindow != nullptr) delete meleeWindow;
    if(kiWindow != nullptr) delete kiWindow;
    if(moveWindow != nullptr) delete moveWindow;

    generalWindow = new GeneralFrame(pak->GetParamData(PARAM_TYPE_GENERAL), this);
    meleeWindow = new MeleeFrame(pak->GetParamData(PARAM_TYPE_MELEE), this);
    kiWindow = new KiFrame(pak->GetParamData(PARAM_TYPE_KI_BLAST), this);
    moveWindow = new MovementFrame(pak->GetParamData(PARAM_TYPE_MOVEMENT), this);

    ui->GeneralScrollArea->setWidget(generalWindow);
    ui->MeleeScrollArea->setWidget(meleeWindow);
    ui->KiBlastScrollArea->setWidget(kiWindow);
    ui->MovementScrollArea->setWidget(moveWindow);

    ui->ParameterTabs->setCurrentIndex(PARAM_TYPE_GENERAL);
}

void NeoStudio::InitDatFile()
{
    Debug::Log("InitDatFile called.", Debug::INFO);

    datIndex = (ParameterType)(file.split('/')[(file.split('/').length()-1)].split("_")[0].toInt() - 17);

    if(datIndex == PARAM_TYPE_INVALID)
    {
        Debug::Log("Invalid .dat file.", Debug::ERROR);
        return;
    }

    int tabCount = ui->ParameterTabs->count();

    for(int i=0;i<tabCount;i++)
    {
        ui->ParameterTabs->setTabEnabled(i, false);
    }

    ui->ParameterTabs->setTabEnabled(datIndex, true);

    switch(datIndex)
    {
        case PARAM_TYPE_GENERAL:
            generalWindow = new GeneralFrame(FileParse::ReadWholeFile(file));
            ui->GeneralScrollArea->setWidget(generalWindow);
            break;
        case PARAM_TYPE_MELEE:
            meleeWindow = new MeleeFrame(FileParse::ReadWholeFile(file));
            ui->MeleeScrollArea->setWidget(meleeWindow);
            break;
        case PARAM_TYPE_KI_BLAST:
            kiWindow = new KiFrame(FileParse::ReadWholeFile(file));
            ui->KiBlastScrollArea->setWidget(kiWindow);
            break;
        case PARAM_TYPE_MOVEMENT:
            moveWindow = new MovementFrame(FileParse::ReadWholeFile(file));
            ui->MovementScrollArea->setWidget(moveWindow);
            break;
        default:
            Debug::Log("Invalid .dat file.", Debug::ERROR);
            return;
    }
    ui->ParameterTabs->setCurrentIndex(datIndex);
}

void NeoStudio::ExportDat()
{
    Debug::Log("ExportDat called.", Debug::INFO);

    if(file.isEmpty())
    {
        Debug::Log("No file opened.", Debug::ERROR);
        return;
    }
    if(file.toLower().endsWith(".dat"))
    {
        Debug::Log("Export isn't supported for .dat files. Using 'SaveAs' instead.", Debug::WARNING);
        SaveFileAs();
    }

    int type = ui->ParameterTabs->currentIndex();

    QString saveDir = QFileDialog::getExistingDirectory(this, "Export .dat file to...", file);

    if(saveDir.isEmpty())
    {
        Debug::Log("No directory selected.", Debug::ERROR);
        return;
    }

    // For some reason, the switch below will not work without turning it into a variable first.
    QByteArray* pakData = new QByteArray(pak->GetParamData((ParameterType)type));

    QByteArray* paramData;
    switch(type)
    {
        case PARAM_TYPE_GENERAL:
            if(pakData->compare(*generalWindow->gp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = generalWindow->gp->GetFileData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case PARAM_TYPE_MELEE:
            if(pakData->compare(*meleeWindow->mp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = meleeWindow->mp->GetFileData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case PARAM_TYPE_KI_BLAST:
            if(pakData->compare(*kiWindow->kp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = kiWindow->kp->GetFileData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case PARAM_TYPE_MOVEMENT:
            if(pakData->compare(*moveWindow->mp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = moveWindow->mp->GetFileData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        default:
            Debug::Log("This parameter section isn't supported yet.", Debug::ERROR);
            return;
    }
    FileParse::WriteFile(saveDir + filenameDat[type], paramData);
}

void NeoStudio::ImportDat()
{
    Debug::Log("ImportDat called.", Debug::INFO);

    if(file.isEmpty())
    {
        Debug::Log("No file opened.", Debug::ERROR);
        return;
    }
    else if(!file.toLower().endsWith(".pak"))
    {
        Debug::Log("Opened file isn't a .pak file.", Debug::ERROR);
        return;
    }

    QString datPath = QFileDialog::getOpenFileName(this, "Open .dat file", file, "Parameter Files (*.dat)");
    if(datPath.isEmpty())
    {
        Debug::Log("No path selected.", Debug::ERROR);
        return;
    }
    QByteArray datData = FileParse::ReadWholeFile(datPath);

    datPath = datPath.split("/")[datPath.split("/").count()-1];
    int datIndex = datPath.split("_")[0].toInt();

    switch(++datIndex - PARAM_OFFSET_GENERAL)
    {
        case PARAM_TYPE_GENERAL:
            generalWindow->gp->SetFileData(datData);
            generalWindow->InitializeUIElements();
            break;
        case PARAM_TYPE_MELEE:
            meleeWindow->mp->SetFileData(datData);
            meleeWindow->ui->AttackSelectionBox->setCurrentIndex(0);
            meleeWindow->InitializeUIElements();
            break;
        case PARAM_TYPE_KI_BLAST:
            kiWindow->kp->SetFileData(datData);
            kiWindow->ui->KiBlastSelectionBox->setCurrentIndex(0);
            kiWindow->InitializeUIElements();
            break;
        case PARAM_TYPE_MOVEMENT:
            moveWindow->mp->SetFileData(datData);
            moveWindow->InitializeUIElements();
            break;
        default:
            Debug::Log("This parameter section isn't supported yet.", Debug::ERROR);
    }
}


void NeoStudio::ResetUiMode()
{
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));

    if(generalWindow != nullptr)
        generalWindow->ResetUiMode();
    if(meleeWindow != nullptr)
        meleeWindow->ResetUiMode();
    if(kiWindow != nullptr)
        kiWindow->ResetUiMode();
    if(moveWindow != nullptr)
        moveWindow->ResetUiMode();
}
