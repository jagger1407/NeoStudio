#include "neostudio.h"
#include "ui_neostudio.h"


#define VERSION_STRING "Neo Studio v1.0"


NeoStudio::NeoStudio(int argc, char* argv[], QWidget* parent) :
    QMainWindow(parent), ui(new Ui::NeoStudio)
{
    if(argc > 2) return;

    options = new Options();

    ui->setupUi(this);
    this->setWindowTitle(VERSION_STRING);
    ui->ParameterTabs->setCurrentIndex(GENERAL);
    ResetUiMode();

    QGraphicsScene* scene = new QGraphicsScene();
    // Drip Code
    scene->addPixmap((*new QPixmap("./assets/UnderConstruction.png")).scaled(ui->graphicsView_1->width(), ui->graphicsView_1->height()));
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
    Debug::Log("NeoStudio constructed.", Debug::INFO, options);
}

NeoStudio::~NeoStudio() = default;

void NeoStudio::OpenFile()
{
    Debug::Log("OpenFile slot triggered.", Debug::INFO, options);

    QString filePath = QFileDialog::getOpenFileName(this,
                                        "Open File", "/home", "Character Files (*.pak);;Parameter Files (*.dat)");
    if(filePath.isEmpty())
    {
        Debug::Log("OpenFile: No file selected.", Debug::WARNING, options);
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
    Debug::Log("SaveFile slot triggered.", Debug::INFO, options);
    if(file == NULL)
    {
        Debug::Log("SaveFile: No file open.", Debug::ERROR, options);
        return;
    }
    if(file.toLower().endsWith(".pak"))
    {
        pak->UpdateParamData(GENERAL, generalWindow->gp->GetFileData());
        pak->UpdateParamData(MELEE, meleeWindow->mp->GetFileData());
        pak->UpdateParamData(KI_BLAST, kiWindow->kp->GetFileData());
        pak->UpdateParamData(MOVEMENT, moveWindow->mp->GetFileData());
        pak->SavePak(file);
    }
    else if(file.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case GENERAL:
                datPtr = new QByteArray(generalWindow->gp->GetFileData());
                break;
            case MELEE:
                datPtr = new QByteArray(meleeWindow->mp->GetFileData());
                break;
            case KI_BLAST:
                datPtr = new QByteArray(kiWindow->kp->GetFileData());
                break;
            case MOVEMENT:
                datPtr = new QByteArray(moveWindow->mp->GetFileData());
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR, options);
                return;
        }
        FileParse::WriteFile(file, datPtr);
    }
}

void NeoStudio::SaveFileAs()
{
    Debug::Log("SaveFileAs slot triggered.", Debug::INFO, options);
    if(file == NULL)
    {
        Debug::Log("SaveFileAs: No file open.", Debug::ERROR, options);
        return;
    }

    QString newFile;
    if(file.toLower().endsWith(".pak"))
        newFile = QFileDialog::getSaveFileName(this, "Save File", "/home", "Character Files (*.pak)");
    else if(file.toLower().endsWith(".dat"))
        newFile = QFileDialog::getSaveFileName(this, "Save File", "/home", "Parameter Files (*.dat)");
    if(newFile == NULL)
    {
        Debug::Log("SaveFileAs: No file selected.", Debug::WARNING, options);
        return;
    }

    if(newFile.toLower().endsWith(".pak"))
    {
        pak->UpdateParamData(GENERAL, generalWindow->gp->GetFileData());
        pak->UpdateParamData(MELEE, meleeWindow->mp->GetFileData());
        pak->UpdateParamData(KI_BLAST, kiWindow->kp->GetFileData());
        pak->UpdateParamData(MOVEMENT, moveWindow->mp->GetFileData());
        pak->SavePak(newFile);
    }
    else if(newFile.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case GENERAL:
                datPtr = new QByteArray(generalWindow->gp->GetFileData());
                break;
            case MELEE:
                datPtr = new QByteArray(meleeWindow->mp->GetFileData());
                break;
            case KI_BLAST:
                datPtr = new QByteArray(kiWindow->kp->GetFileData());
                break;
            case MOVEMENT:
                datPtr = new QByteArray(moveWindow->mp->GetFileData());
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR, options);
                return;
        }
        FileParse::WriteFile(newFile, datPtr);
    }
}

void NeoStudio::CloseFile()
{
    if(file == NULL)
    {
        Debug::Log("CloseFile: No file open.", Debug::ERROR, options);
        return;
    }
    Debug::Log("CloseFile slot triggered.", Debug::INFO, options);
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
    Debug::Log("About page opened.", Debug::INFO, options);
    AboutWindow(options).exec();
}
void NeoStudio::OpenOptions()
{
    Debug::Log("Option Dialog opened.", Debug::INFO, options);
    OptionDialog* optionWindow = new OptionDialog(options);
    optionWindow->exec();
    ResetUiMode();
    if(generalWindow != nullptr) generalWindow->ResetUiMode();
    if(meleeWindow != nullptr) meleeWindow->ResetUiMode();
    if(kiWindow != nullptr) kiWindow->ResetUiMode();
    if(moveWindow != nullptr) moveWindow->ResetUiMode();
    delete optionWindow;
}


void NeoStudio::InitPakFile()
{
    Debug::Log("InitPakFile called.", Debug::INFO, options);
    pak = new PakControls(file, options);
    if(pak->HasFailed()) return;

    if(generalWindow != nullptr) delete generalWindow;
    if(meleeWindow != nullptr) delete meleeWindow;
    if(kiWindow != nullptr) delete kiWindow;
    if(moveWindow != nullptr) delete moveWindow;

    generalWindow = new GeneralFrame(pak->GetParamData(GENERAL), options, this);
    meleeWindow = new MeleeFrame(pak->GetParamData(MELEE), options, this);
    kiWindow = new KiFrame(pak->GetParamData(KI_BLAST), options, this);
    moveWindow = new MovementFrame(pak->GetParamData(MOVEMENT), options, this);

    ui->GeneralScrollArea->setWidget(generalWindow);
    ui->MeleeScrollArea->setWidget(meleeWindow);
    ui->KiBlastScrollArea->setWidget(kiWindow);
    ui->MovementScrollArea->setWidget(moveWindow);

    ui->ParameterTabs->setCurrentIndex(GENERAL);
}

void NeoStudio::InitDatFile()
{
    Debug::Log("InitDatFile called.", Debug::INFO, options);

    datIndex = (ParameterType)(file.split('/')[(file.split('/').length()-1)].split("_")[0].toInt() - 17);

    if(datIndex == PARAM_TYPE_INVALID)
    {
        Debug::Log("Invalid .dat file.", Debug::ERROR, options);
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
        case GENERAL:
            generalWindow = new GeneralFrame(FileParse::ReadWholeFile(file), options);
            ui->GeneralScrollArea->setWidget(generalWindow);
            break;
        case MELEE:
            meleeWindow = new MeleeFrame(FileParse::ReadWholeFile(file), options);
            ui->MeleeScrollArea->setWidget(meleeWindow);
            break;
        case KI_BLAST:
            kiWindow = new KiFrame(FileParse::ReadWholeFile(file), options);
            ui->KiBlastScrollArea->setWidget(kiWindow);
            break;
        case MOVEMENT:
            moveWindow = new MovementFrame(FileParse::ReadWholeFile(file), options);
            ui->MovementScrollArea->setWidget(moveWindow);
            break;
        default:
            Debug::Log("Invalid .dat file.", Debug::ERROR, options);
            return;
    }
    ui->ParameterTabs->setCurrentIndex(datIndex);
}

void NeoStudio::ExportDat()
{
    Debug::Log("ExportDat called.", Debug::INFO, options);

    if(file.isEmpty())
    {
        Debug::Log("No file opened.", Debug::ERROR, options);
        return;
    }
    if(file.toLower().endsWith(".dat"))
    {
        Debug::Log("Export isn't supported for .dat files. Use 'Save'/'Save As' instead.", Debug::ERROR, options);
        return;
    }

    int type = ui->ParameterTabs->currentIndex();

    QString saveDir = QFileDialog::getExistingDirectory(this, "Export .dat file to...", file);

    if(saveDir.isEmpty())
    {
        Debug::Log("No directory selected.", Debug::ERROR, options);
        return;
    }

    // For some reason, the switch below will not work without turning it into a variable first.
    QByteArray* pakData = new QByteArray(pak->GetParamData((ParameterType)type));

    QByteArray* paramData;
    switch(type)
    {
        case GENERAL:
            if(pakData->compare(generalWindow->gp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat(options))
                    paramData = new QByteArray(generalWindow->gp->GetFileData());
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case MELEE:
            if(pakData->compare(meleeWindow->mp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat(options))
                    paramData = new QByteArray(meleeWindow->mp->GetFileData());
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case KI_BLAST:
            if(pakData->compare(kiWindow->kp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat(options))
                    paramData = new QByteArray(kiWindow->kp->GetFileData());
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        case MOVEMENT:
            if(pakData->compare(moveWindow->mp->GetFileData()))
            {
                if(DatSelectionDialog::SelectDat(options))
                    paramData = new QByteArray(moveWindow->mp->GetFileData());
                else
                    paramData = pakData;
            }
            else
                paramData = pakData;
            break;
        default:
            Debug::Log("This parameter section isn't supported yet.", Debug::ERROR, options);
            return;
    }
    FileParse::WriteFile(saveDir + filenameDat[type], paramData);
}

void NeoStudio::ImportDat()
{
    Debug::Log("ImportDat called.", Debug::INFO, options);

    if(file.isEmpty())
    {
        Debug::Log("No file opened.", Debug::ERROR, options);
        return;
    }
    else if(!file.toLower().endsWith(".pak"))
    {
        Debug::Log("Opened file isn't a .pak file.", Debug::ERROR, options);
        return;
    }

    QString datPath = QFileDialog::getOpenFileName(this, "Open .dat file", file, "Parameter Files (*.dat)");
    if(datPath.isEmpty())
    {
        Debug::Log("No path selected.", Debug::ERROR, options);
        return;
    }
    QByteArray datData = FileParse::ReadWholeFile(datPath);

    datPath = datPath.split("/")[datPath.split("/").count()-1];
    int datIndex = datPath.split("_")[0].toInt();

    switch(++datIndex - GENERAL_OFFSET)
    {
        case GENERAL:
            generalWindow->gp->SetFileData(datData);
            generalWindow->InitializeUIElements();
            break;
        case MELEE:
            meleeWindow->mp->SetFileData(datData);
            meleeWindow->ui->AttackSelectionBox->setCurrentIndex(0);
            meleeWindow->InitializeUIElements();
            break;
        case KI_BLAST:
            kiWindow->kp->SetFileData(datData);
            kiWindow->ui->KiBlastSelectionBox->setCurrentIndex(0);
            kiWindow->InitializeUIElements();
            break;
        case MOVEMENT:
            moveWindow->mp->SetFileData(datData);
            moveWindow->InitializeUIElements();
            break;
        default:
            Debug::Log("This parameter section isn't supported yet.", Debug::ERROR, options);
    }
}


void NeoStudio::ResetUiMode()
{
    if(options->GetUiMode() == Options::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");
        ui->MenuBar->setStyleSheet("background:white");
        ui->GeneralScrollArea->setStyleSheet("color:black");
        ui->MeleeScrollArea->setStyleSheet("color:black");
        ui->KiBlastScrollArea->setStyleSheet("color:black");
        ui->MovementScrollArea->setStyleSheet("color:black");
        ui->FileLbl->setStyleSheet("color:black");
        ui->GeneralTab->setStyleSheet("color:black;background:white;");
        ui->MeleeTab->setStyleSheet("color:black;background:white;");
        ui->KiBlastTab->setStyleSheet("color:black;background:white;");
        ui->MovementTab->setStyleSheet("color:black;background:white;");
    }
    else if(options->GetUiMode() == Options::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");
        ui->MenuBar->setStyleSheet("background-color:rgb(75, 81, 90)");
        ui->GeneralScrollArea->setStyleSheet("color:white");
        ui->MeleeScrollArea->setStyleSheet("color:white");
        ui->KiBlastScrollArea->setStyleSheet("color:white");
        ui->MovementScrollArea->setStyleSheet("color:white");
        ui->FileLbl->setStyleSheet("color:white");
        ui->GeneralTab->setStyleSheet("color:black;background:rgb(50,54,60);");
        ui->MeleeTab->setStyleSheet("color:black;background:rgb(50,54,60);");
        ui->KiBlastTab->setStyleSheet("color:black;background:rgb(50,54,60);");
        ui->MovementTab->setStyleSheet("color:black;background:rgb(50,54,60);");
    }
}
