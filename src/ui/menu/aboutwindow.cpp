#include "aboutwindow.h"

AboutWindow::AboutWindow()
    : ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    unsigned char currentMode = OptionProcessing::GetOption("UiMode");

    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(ui->graphicsView->rect());
    scene->addPixmap(QPixmap("./assets/AboutImage.png").scaled(ui->graphicsView->width(), ui->graphicsView->height(), Qt::KeepAspectRatio));
    ui->graphicsView->setScene(scene);
    if(currentMode == OptionProcessing::LIGHT)
    {
        setStyleSheet("background:white; color: black");
    }
    else if(currentMode == OptionProcessing::DARK)
    {
        setStyleSheet("background:rgb(50, 54, 60) ; color: white");
    }
}
