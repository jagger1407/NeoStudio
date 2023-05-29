#include "ui/neostudio.h"
#include "external/qt_includes.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    NeoStudio* w = new NeoStudio(argc, argv);
    w->show();

    return app.exec();
}

