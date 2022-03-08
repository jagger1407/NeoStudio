#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget* parent) :
    QDialog(parent),
ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(ui->graphicsView->rect());
    scene->addPixmap(QPixmap("./assets/AboutImage.png").scaled(ui->graphicsView->width(), ui->graphicsView->height(), Qt::KeepAspectRatio));
    ui->graphicsView->setScene(scene);
}
AboutWindow::~AboutWindow() = default;
