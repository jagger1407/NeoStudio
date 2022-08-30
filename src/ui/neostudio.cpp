#include "neostudio.h"
#include "ui_neostudio.h"

NeoStudio::NeoStudio(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::NeoStudio)
{
    ui->setupUi(this);
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
    Debug::Log("OpenFile called.", Debug::INFO);
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
    Debug::Log("SaveFile called.", Debug::INFO);
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
    Debug::Log("SaveFileAs called.", Debug::INFO);
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
    Debug::Log("CloseFile called.", Debug::INFO);
    if(generalWindow == nullptr) return;
    generalWindow->close();
    file = "";
}

void NeoStudio::OpenAbout()
{
    Debug::Log("About page opened.", Debug::INFO);
    (new AboutWindow())->exec();
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
