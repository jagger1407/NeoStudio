#include "neostudio.h"
#include "ui_neostudio.h"


#define VERSION_STRING "Neo Studio v0.5"


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
    //ui->graphicsView_2->setScene(scene);
    ui->graphicsView_3->setScene(scene);

    if(argc == 2)
    {
        file = argv[1];
        QString PakName = file.split('/')[(file.split('/').length()-1)];
        PakName.truncate(PakName.length()-4);
        ui->FileLbl->setText("Current File: " + PakName);
        InitPakFile();
    }
    Debug::Log("NeoStudio constructed.", Debug::INFO, options);
}

NeoStudio::~NeoStudio() = default;

void NeoStudio::OpenFile()
{
    Debug::Log("OpenFile slot triggered.", Debug::INFO, options);
    file = QFileDialog::getOpenFileName(this,
                                        "Open File", "/home", "Character Files (*.pak)(*.pak);;Parameter Files (*.dat)(*.dat)");
    if(file == NULL)
    {
        Debug::Log("OpenFile: No file selected.", Debug::WARNING, options);
        return;
    }

    for(int i=0;i<ui->ParameterTabs->count();i++) ui->ParameterTabs->setTabEnabled(i, true);

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
        pak->SavePak(file);
    }
    else if(file.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case GENERAL:
                datPtr = new QByteArray(generalWindow->gp->GetFileData());
                FileParse::WriteFile(file, datPtr);
                break;
            case MELEE:
                datPtr = new QByteArray(meleeWindow->mp->GetFileData());
                FileParse::WriteFile(file, datPtr);
                break;
            case KI_BLAST:
                datPtr = new QByteArray(kiWindow->kp->GetFileData());
                FileParse::WriteFile(file, datPtr);
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR, options);
        }
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

    QString newFile = QFileDialog::getSaveFileName(this,
                                                   "Save File", "/home", "Character Files (*.pak)(*.pak);;Parameter Files (*.dat)(*.dat)");
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
        pak->SavePak(file);
    }
    else if(newFile.toLower().endsWith(".dat"))
    {
        QByteArray* datPtr;
        switch(datIndex)
        {
            case GENERAL:
                datPtr = new QByteArray(generalWindow->gp->GetFileData());
                FileParse::WriteFile(newFile, datPtr);
                break;
            case MELEE:
                datPtr = new QByteArray(meleeWindow->mp->GetFileData());
                FileParse::WriteFile(newFile, datPtr);
                break;
            case KI_BLAST:
                datPtr = new QByteArray(kiWindow->kp->GetFileData());
                FileParse::WriteFile(newFile, datPtr);
                break;
            default:
                Debug::Log("Invalid .dat file.", Debug::ERROR, options);
        }
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

    generalWindow = new GeneralFrame(pak->GetParamData(GENERAL), options);
    meleeWindow = new MeleeFrame(pak->GetParamData(MELEE), options);
    kiWindow = new KiFrame(pak->GetParamData(KI_BLAST), options);

    ui->GeneralScrollArea->setWidget(generalWindow);
    ui->MeleeScrollArea->setWidget(meleeWindow);
    ui->KiBlastScrollArea->setWidget(kiWindow);

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
        default:
            Debug::Log("Invalid .dat file.", Debug::ERROR, options);
            return;
    }
    ui->ParameterTabs->setCurrentIndex(datIndex);
}


void NeoStudio::ResetUiMode()
{
    if(options->GetUiMode() == Options::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");
        ui->GeneralScrollArea->setStyleSheet("color:black");
        ui->MeleeScrollArea->setStyleSheet("color:black");
        ui->FileLbl->setStyleSheet("color:black");
        ui->GeneralTab->setStyleSheet("color:black;background:white;");
        ui->MeleeTab->setStyleSheet("color:black;background:white;");
    }
    else if(options->GetUiMode() == Options::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");
        ui->GeneralScrollArea->setStyleSheet("color:white");
        ui->MeleeScrollArea->setStyleSheet("color:white");
        ui->FileLbl->setStyleSheet("color:white");
        ui->GeneralTab->setStyleSheet("color:black;background:rgb(50,54,60);");
        ui->MeleeTab->setStyleSheet("color:black;background:rgb(50,54,60);");
    }
}
