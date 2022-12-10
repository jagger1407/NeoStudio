#include "aboutwindow.h"

AboutWindow::AboutWindow(Options* options)
    : ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(ui->graphicsView->rect());
    scene->addPixmap(QPixmap("./assets/AboutImage.png").scaled(ui->graphicsView->width(), ui->graphicsView->height(), Qt::KeepAspectRatio));
    ui->graphicsView->setScene(scene);
    if(options->GetUiMode() == Options::LIGHT)
    {
        setStyleSheet("background:white; color: black");
    }
    else if(options->GetUiMode() == Options::DARK)
    {
        setStyleSheet("background:rgb(50, 54, 60) ; color: white");
    }
}
