#include "ui/neostudio.h"
#include "external/debug.h"
#include "external/qt_includes.h"

/**Setting this will change what will be visibly logged.*/
Debug::LogMode Debug::CurrentLogMode = Debug::DEV_NOFILE;
/**Setting this will change what color the tooltips will be (shoutout to ViveTheVillain)*/
NeoStudio::TooltipColor ToolTipColor = NeoStudio::BLACK;

// Note: the two settings above will be made available to change inside the program in the next update.

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    NeoStudio w;
    w.show();

    return app.exec();
}

