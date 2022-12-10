#include "neostudio.h"
#include "ui_neostudio.h"

NeoStudio::NeoStudio(int argc, char* argv[], QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::NeoStudio)
{
    options = new Options();

    if(argc > 2) return;

    ui->setupUi(this);
    this->setWindowTitle("Neo Studio v0.3");
    ui->ParameterTabs->setCurrentIndex(GENERAL);
    ResetUiMode();

    QGraphicsScene* scene = new QGraphicsScene();
    // Drip Code
    scene->addPixmap((*new QPixmap("./assets/UnderConstruction.png")).scaled(ui->graphicsView_1->width(), ui->graphicsView_1->height()));
    this->setWindowIcon(QIcon(QPixmap("./assets/icon.ico")));
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_3->setScene(scene);

    if(argc == 2)
    {
        file = argv[1];
        QString PakName = file.split('/')[(file.split('/').length()-1)];
        PakName.truncate(PakName.length()-4);
        ui->FileLbl->setText("Current File: " + PakName);
        InitFile();
    }
    Debug::Log("NeoStudio constructed.", Debug::INFO, options);
}

NeoStudio::~NeoStudio() = default;

void NeoStudio::OpenFile()
{
    Debug::Log("OpenFile slot triggered.", Debug::INFO, options);
    file = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "/home",
                                                tr("Character Files (*.pak)(*.pak)"));//;;Parameter Files (*.dat)(*.dat)"));    This feature might be implemented at some point
    if(file == NULL)
    {
        Debug::Log("OpenFile: No file selected.", Debug::WARNING, options);
        return;
    }
    QString PakName = file.split('/')[(file.split('/').length()-1)];
    PakName.truncate(PakName.length()-4);
    ui->FileLbl->setText("Current File: " + PakName);
    InitFile();
}

void NeoStudio::SaveFile()
{
    Debug::Log("SaveFile slot triggered.", Debug::INFO, options);
    if(file == NULL)
    {
        Debug::Log("SaveFile: No file open.", Debug::ERROR, options);
        return;
    }

    pak->UpdateParamData(GENERAL, generalWindow->gp->GetFileData());
    pak->UpdateParamData(MELEE, meleeWindow->mp->GetFileData());
    pak->SavePak(file);
}

void NeoStudio::SaveFileAs()
{
    Debug::Log("SaveFileAs slot triggered.", Debug::INFO, options);
    if(file == NULL)
    {
        Debug::Log("SaveFileAs: No file open.", Debug::ERROR, options);
        return;
    }

    QString newFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                "/home",
                                                tr("Character Files (*.pak)(*.pak)"));//;;Parameter Files (*.dat)(*.dat)"));    This feature might be implemented at some point
    if(newFile == NULL)
    {
        Debug::Log("SaveFileAs: No file selected.", Debug::WARNING, options);
        return;
    }
    pak->UpdateParamData(GENERAL, generalWindow->gp->GetFileData());
    pak->UpdateParamData(MELEE, meleeWindow->mp->GetFileData());
    pak->SavePak(newFile);
}

void NeoStudio::CloseFile()
{
    if(file == NULL)
    {
        Debug::Log("CloseFile: No file open.", Debug::ERROR, options);
        return;
    }
    Debug::Log("CloseFile slot triggered.", Debug::INFO, options);
    if(generalWindow == nullptr) return;
    generalWindow->close();
    file = "";
    ui->FileLbl->setText("Open A Character File...");
}

void NeoStudio::OpenAbout()
{
    Debug::Log("About page opened.", Debug::INFO, options);
    AboutWindow(options).exec();
}
void NeoStudio::OpenOptions()
{
    Debug::Log("Option Dialog opened.", Debug::INFO, options);
    OptionDialog(options).exec();
    ResetUiMode();
    if(generalWindow != nullptr) generalWindow->ResetUiMode();
    if(meleeWindow != nullptr) meleeWindow->ResetUiMode();
}


void NeoStudio::InitFile()
{
    Debug::Log("InitFile called.", Debug::INFO, options);
    pak = new PakControls(file, options);
    if(pak->HasFailed()) return;
    ui->ParameterTabs->setCurrentIndex(GENERAL);
    generalWindow = new GeneralFrame(pak, options);
    ui->GeneralScrollArea->setWidget(generalWindow);
    meleeWindow = new MeleeFrame(pak, options);
    ui->MeleeScrollArea->setWidget(meleeWindow);
}

void NeoStudio::ResetUiMode()
{
    if(options->GetUiMode() == Options::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");
        ui->FileLbl->setStyleSheet("color:black");
        ui->GeneralTab->setStyleSheet("color:black;background:white;");
        ui->MeleeTab->setStyleSheet("color:black;background:white;");
    }
    else if(options->GetUiMode() == Options::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");
        ui->FileLbl->setStyleSheet("color:white");
        ui->GeneralTab->setStyleSheet("color:black;background:rgb(50,54,60);");
        ui->MeleeTab->setStyleSheet("color:black;background:rgb(50,54,60);");
    }
}

