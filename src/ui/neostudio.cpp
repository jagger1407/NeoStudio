#include "neostudio.h"
#include "ui_neostudio.h"

#include "src/ui/menu/characterselectiondialog.h"

#define VERSION_STRING "Neo Studio v1.1.4"

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
        pak->UpdateParamData(PARAM_OFFSET_GENERAL, generalWindow->gp->GetParameterData());
        pak->UpdateParamData(PARAM_OFFSET_MELEE, meleeWindow->mp->GetParameterData());
        pak->UpdateParamData(PARAM_OFFSET_KI_BLAST, kiWindow->kp->GetParameterData());
        pak->UpdateParamData(PARAM_OFFSET_MOVEMENT, moveWindow->mp->GetParameterData());
        pak->SavePak(file);
    }
    else if(file.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case PARAM_TYPE_GENERAL:
                datPtr = generalWindow->gp->GetParameterData();
                break;
            case PARAM_TYPE_MELEE:
                datPtr = meleeWindow->mp->GetParameterData();
                break;
            case PARAM_TYPE_KI_BLAST:
                datPtr = kiWindow->kp->GetParameterData();
                break;
            case PARAM_TYPE_MOVEMENT:
                datPtr = moveWindow->mp->GetParameterData();
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR);
                return;
        }
        FileParse::WriteFile(file, datPtr);

        if(FileParse::DoesFileExist(file))
        {
            Debug::Log("File '" + file + "' saved successfully.", Debug::INFO);
        }
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
        pak->UpdateParamData(PARAM_OFFSET_GENERAL, generalWindow->gp->GetParameterData());
        pak->UpdateParamData(PARAM_OFFSET_MELEE, meleeWindow->mp->GetParameterData());
        pak->UpdateParamData(PARAM_OFFSET_KI_BLAST, kiWindow->kp->GetParameterData());
        pak->UpdateParamData(PARAM_OFFSET_MOVEMENT, moveWindow->mp->GetParameterData());
        pak->SavePak(newFile);
        if(FileParse::DoesFileExist(newFile))
        {
            Debug::Log("File '" + newFile + "' saved successfully.", Debug::INFO);
        }
    }
    else if(newFile.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case PARAM_TYPE_GENERAL:
                datPtr = generalWindow->gp->GetParameterData();
                break;
            case PARAM_TYPE_MELEE:
                datPtr = meleeWindow->mp->GetParameterData();
                break;
            case PARAM_TYPE_KI_BLAST:
                datPtr = kiWindow->kp->GetParameterData();
                break;
            case PARAM_TYPE_MOVEMENT:
                datPtr = moveWindow->mp->GetParameterData();
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR);
                return;
        }
        FileParse::WriteFile(newFile, datPtr);
        delete datPtr;
        if(FileParse::DoesFileExist(newFile))
        {
            Debug::Log("File '" + newFile + "' saved successfully.", Debug::INFO);
        }
    }
}

void NeoStudio::CloseFile()
{
    if(file == NULL)
    {
        Debug::Log("CloseFile: No file open.", Debug::ERROR);
        return;
    }
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

    if(generalWindow != nullptr) delete generalWindow;
    if(meleeWindow != nullptr) delete meleeWindow;
    if(kiWindow != nullptr) delete kiWindow;
    if(moveWindow != nullptr) delete moveWindow;

    generalWindow = new GeneralFrame(pak->GetParamData(PARAM_OFFSET_GENERAL), this);
    meleeWindow = new MeleeFrame(pak->GetParamData(PARAM_OFFSET_MELEE), this);
    kiWindow = new KiFrame(pak->GetParamData(PARAM_OFFSET_KI_BLAST), this);
    moveWindow = new MovementFrame(pak->GetParamData(PARAM_OFFSET_MOVEMENT), this);

    ui->GeneralScrollArea->setWidget(generalWindow);
    ui->MeleeScrollArea->setWidget(meleeWindow);
    ui->KiBlastScrollArea->setWidget(kiWindow);
    ui->MovementScrollArea->setWidget(moveWindow);

    ui->ParameterTabs->setCurrentIndex(PARAM_TYPE_GENERAL);
}

void NeoStudio::InitDatFile()
{
    datIndex = (ParameterType)(file.split('/')[(file.split('/').length()-1)].split("_")[0].toInt() - 17);

    if(datIndex <= PARAM_TYPE_INVALID || datIndex >= PARAM_TYPE_NEXT)
    {
        Debug::Log("Invalid .dat file.", Debug::ERROR);
        Debug::Log("datIndex = " + QString::number((int)datIndex), Debug::INFO);
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
            Debug::Log("No Frame available for this Parameter Type.", Debug::ERROR);
            return;
    }
    ui->ParameterTabs->setCurrentIndex(datIndex);
}

void NeoStudio::ExportDat()
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
    }

    int type = ui->ParameterTabs->currentIndex();

    QString saveDir = QFileDialog::getExistingDirectory(this, "Export .dat file to...", file);

    if(saveDir.isEmpty())
    {
        Debug::Log("No directory selected.", Debug::ERROR);
        return;
    }

    // For some reason, the switch below will not work without turning it into a variable first.
    QByteArray* pakData = new QByteArray(pak->GetParamData(type + PARAM_OFFSET_GENERAL));

    QByteArray* paramData;
    switch(type)
    {
        case PARAM_TYPE_GENERAL:
            if(pakData->compare(*generalWindow->gp->GetParameterData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = generalWindow->gp->GetParameterData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case PARAM_TYPE_MELEE:
            if(pakData->compare(*meleeWindow->mp->GetParameterData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = meleeWindow->mp->GetParameterData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case PARAM_TYPE_KI_BLAST:
            if(pakData->compare(*kiWindow->kp->GetParameterData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = kiWindow->kp->GetParameterData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case PARAM_TYPE_MOVEMENT:
            if(pakData->compare(*moveWindow->mp->GetParameterData()))
            {
                if(DatSelectionDialog::SelectDat())
                    paramData = moveWindow->mp->GetParameterData();
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        default:
            Debug::Log("This parameter section isn't supported yet.", Debug::ERROR);
            delete pakData;
            return;
    }

    if(!FileParse::DoesFileExist(pak->sectionNameFile))
    {
        Debug::Log("Section Name List (" + pak->sectionNameFile + ") doesn't exist.", Debug::ERROR);
        delete pakData;
        return;
    }
    QStringList sectionNames = FileParse::ReadLines(pak->sectionNameFile);
    FileParse::WriteFile(saveDir + "/" + sectionNames[type + PARAM_OFFSET_GENERAL], paramData);
    delete pakData;
    if(FileParse::DoesFileExist(saveDir + "/" + sectionNames[type + PARAM_OFFSET_GENERAL]))
    {
        Debug::Log("File '" + sectionNames[type + PARAM_OFFSET_GENERAL] + "' saved successfully.", Debug::INFO);
    }
}

void NeoStudio::ImportDat()
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

    QString datPath = QFileDialog::getOpenFileName(this, "Open .dat file", file, "Parameter Files (*.dat)");
    if(datPath.isEmpty())
    {
        Debug::Log("No path selected.", Debug::WARNING);
        return;
    }
    QByteArray datData = FileParse::ReadWholeFile(datPath);

    datPath = datPath.split("/")[datPath.split("/").count()-1];
    int datIndex = datPath.split("_")[0].toInt();

    switch(datIndex - PARAM_OFFSET_GENERAL)
    {
        case PARAM_TYPE_GENERAL:
            generalWindow->gp->SetParameterData(datData);
            generalWindow->InitializeUIElements();
            break;
        case PARAM_TYPE_MELEE:
            meleeWindow->mp->SetParameterData(datData);
            meleeWindow->ui->AttackSelectionBox->setCurrentIndex(0);
            meleeWindow->InitializeUIElements();
            break;
        case PARAM_TYPE_KI_BLAST:
            kiWindow->kp->SetParameterData(datData);
            kiWindow->ui->KiBlastSelectionBox->setCurrentIndex(0);
            kiWindow->InitializeUIElements();
            break;
        case PARAM_TYPE_MOVEMENT:
            moveWindow->mp->SetParameterData(datData);
            moveWindow->InitializeUIElements();
            break;
        default:
            Debug::Log("This parameter section isn't supported yet.", Debug::ERROR);
            Debug::Log("datIndex = " + QString::number(datIndex), Debug::INFO);
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
