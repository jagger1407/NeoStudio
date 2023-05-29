#include "aboutwindow.h"

AboutWindow::AboutWindow(Options* options)
    : ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    ui->graphicsView_AboutImage->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	ui->graphicsView_AboutImage->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(ui->graphicsView_AboutImage->rect());
    scene->addPixmap(QPixmap("./assets/AboutImage.png").scaled(ui->graphicsView_AboutImage->width(),
                                                               ui->graphicsView_AboutImage->height(),
                                                               Qt::KeepAspectRatio));
    ui->graphicsView_AboutImage->setScene(scene);
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + options->GetUiMode() + ".qss"));
}
