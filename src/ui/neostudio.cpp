#include "neostudio.h"
#include "ui_neostudio.h"

NeoStudio::NeoStudio(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::NeoStudio)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene();
    // Drip Code
    scene->addPixmap((*new QPixmap("../assets/UnderConstruction.png")).scaled(ui->graphicsView_1->width(), ui->graphicsView_1->height()));
    ui->graphicsView_1->setScene(scene);
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_3->setScene(scene);
}

NeoStudio::~NeoStudio() = default;

void NeoStudio::OpenFile()
{
    file = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "/home",
                                                tr("Character Files (*.pak)(*.pak)"));//;;Parameter Files (*.dat)(*.dat)"));    This feature might be implemented at some point
    if(file == NULL)
    {
        Debug::ConsolePrint("Warning! OpenFile: No file selected.");
        return;
    }
    QString PakName = file.split('/')[(file.split('/').length()-1)];
    PakName.truncate(PakName.length()-4);
    ui->FileLbl->setText("Current File: " + PakName);
    InitFile();
}

void NeoStudio::SaveFile()
{
    if(file == NULL)
    {
        Debug::ConsolePrint("Error! SaveFile: No file open.");
        return;
    }

    pak->UpdateParamData(GENERAL, generalWindow->paramData);
    pak->SavePak(file);
}

void NeoStudio::SaveFileAs()
{
    if(file == NULL)
    {
        Debug::ConsolePrint("Error! SaveFileAs: No file open.");
        return;
    }

    QString newFile = QFileDialog::getSaveFileName(this, tr("Open File"),
                                                "/home",
                                                tr("Character Files (*.pak)(*.pak)"));//;;Parameter Files (*.dat)(*.dat)"));    This feature might be implemented at some point
    if(newFile == NULL)
    {
        Debug::ConsolePrint("Warning! SaveFileAs: No file selected.");
        return;
    }

    pak->UpdateParamData(GENERAL, generalWindow->paramData);
    pak->SavePak(newFile);
}

void NeoStudio::CloseFile()
{
    if(generalWindow == nullptr) return;
    generalWindow->close();
    file = "";
}

void NeoStudio::OpenAbout()
{
    (new AboutWindow())->exec();
}

void NeoStudio::InitFile()
{
    pak = new PakControls(file);
    if(pak->HasFailed()) return;
    ui->ParameterTabs->setCurrentIndex(GENERAL);
    generalWindow = new GeneralFrame(pak);
    ui->GeneralScrollArea->setWidget(generalWindow);
}
