#include "ui/neostudio.h"
#include "qt_includes.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    NeoStudio w;
    w.show();

    return app.exec();
}

