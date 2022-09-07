#include "neostudio.h"
#include "ui_neostudio.h"

NeoStudio::NeoStudio(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::NeoStudio)
{
    if(!FileParse::DoesFileExist(CONFIG_PATH))
    {
        OptionProcessing::SaveConfigFile(OptionProcessing::DEFAULT_LOGMODE, OptionProcessing::DEFAULT_TOOLTIPCOLOR, OptionProcessing::DEFAULT_UIMODE);
    }

    ui->setupUi(this);
    this->setWindowTitle("Neo Studio v0.2");
    ResetUiMode();

    QGraphicsScene* scene = new QGraphicsScene();
    // Drip Code
    scene->addPixmap((*new QPixmap("./assets/UnderConstruction.png")).scaled(ui->graphicsView_1->width(), ui->graphicsView_1->height()));
    this->setWindowIcon(QIcon(QPixmap("./assets/icon.ico")));
    ui->graphicsView_1->setScene(scene);
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_3->setScene(scene);
    Debug::Log("NeoStudio constructed.", Debug::INFO);

}

NeoStudio::~NeoStudio() = default;

void NeoStudio::OpenFile()
{
    Debug::Log("OpenFile slot triggered.", Debug::INFO);
    file = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "/home",
                                                tr("Character Files (*.pak)(*.pak)"));//;;Parameter Files (*.dat)(*.dat)"));    This feature might be implemented at some point
    if(file == NULL)
    {
        Debug::Log("OpenFile: No file selected.", Debug::WARNING);
        return;
    }
    QString PakName = file.split('/')[(file.split('/').length()-1)];
    PakName.truncate(PakName.length()-4);
    ui->FileLbl->setText("Current File: " + PakName);
    InitFile();
}

void NeoStudio::SaveFile()
{
    Debug::Log("SaveFile slot triggered.", Debug::INFO);
    if(file == NULL)
    {
        Debug::Log("SaveFile: No file open.", Debug::ERROR);
        return;
    }

    pak->UpdateParamData(GENERAL, generalWindow->gp->GetFileData());
    pak->SavePak(file);
}

void NeoStudio::SaveFileAs()
{
    Debug::Log("SaveFileAs slot triggered.", Debug::INFO);
    if(file == NULL)
    {
        Debug::Log("SaveFileAs: No file open.", Debug::ERROR);
        return;
    }

    QString newFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                "/home",
                                                tr("Character Files (*.pak)(*.pak)"));//;;Parameter Files (*.dat)(*.dat)"));    This feature might be implemented at some point
    if(newFile == NULL)
    {
        Debug::Log("SaveFileAs: No file selected.", Debug::WARNING);
        return;
    }
    pak->UpdateParamData(GENERAL, generalWindow->gp->GetFileData());
    pak->SavePak(newFile);
}

void NeoStudio::CloseFile()
{
    if(file == NULL)
    {
        Debug::Log("CloseFile: No file open.", Debug::ERROR);
        return;
    }
    Debug::Log("CloseFile slot triggered.", Debug::INFO);
    if(generalWindow == nullptr) return;
    generalWindow->close();
    file = "";
    ui->FileLbl->setText("Open A Character File...");
}

void NeoStudio::OpenAbout()
{
    Debug::Log("About page opened.", Debug::INFO);
    (new AboutWindow())->exec();
}
void NeoStudio::OpenOptions()
{
    Debug::Log("Option Dialog opened.", Debug::INFO);
    (new OptionDialog())->exec();
    ResetUiMode();
    if(generalWindow != nullptr) generalWindow->ResetUiMode();
}


void NeoStudio::InitFile()
{
    Debug::Log("InitFile called.", Debug::INFO);
    pak = new PakControls(file);
    if(pak->HasFailed()) return;
    ui->ParameterTabs->setCurrentIndex(GENERAL);
    generalWindow = new GeneralFrame(pak);
    ui->GeneralScrollArea->setWidget(generalWindow);
}

void NeoStudio::ResetUiMode()
{
    unsigned char currentMode = OptionProcessing::GetOption("UiMode");
    if(currentMode == OptionProcessing::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");
        ui->FileLbl->setStyleSheet("color:black");
        ui->GeneralTab->setStyleSheet("color:black;background:white;");
    }
    else if(currentMode == OptionProcessing::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");
        ui->FileLbl->setStyleSheet("color:white");
        ui->GeneralTab->setStyleSheet("color:black;background:rgb(50,54,60);");
    }
}

