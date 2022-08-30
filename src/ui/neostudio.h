#ifndef NEOSTUDIO_H
#define NEOSTUDIO_H

#include "src/external/qt_includes.h"
#include "src/external/debug.h"
#include "aboutwindow.h"
// Parameter Tabs
#include "src/ui/paramSections/generalframe.h"

namespace Ui {
class NeoStudio;
}
/**
 * Main Window User Interface
 */
class NeoStudio : public QMainWindow
{
    Q_OBJECT

public:
    /**A selection of text color choices for tooltips.*/
    typedef enum {
        WHITE,
        BLACK,
        BLUE,
        RED,
    } TooltipColor;
    /**Constructor. Creates the main Neo Studio window.*/
    explicit NeoStudio(QWidget* parent = nullptr);
    /**Destructor. Idk how to use this, it was automatically generated.*/
    ~NeoStudio() override;
private:
    /**QScopedPointer to access UI Elements.*/
    QScopedPointer<Ui::NeoStudio> ui;
    /**The UI for the General Parameter editing tab.*/
    GeneralFrame* generalWindow;
    /**The path to the currently open Pak file.*/
    QString file;
    /**PakControls object to act as an interface between this program and the file itself.*/
    PakControls* pak = nullptr;
    /**Initializes the program using the current Pak filepath.*/
    void InitFile();
private slots:
    /**This slot gets triggered once the 'Open File' menu option is clicked.*/
    void OpenFile();
    /**This slot gets triggered once the 'Save File' menu option is clicked.*/
    void SaveFile();
    /**This slot gets triggered once the 'Save File As' menu option is clicked.*/
    void SaveFileAs();
    /**This slot gets triggered once the 'Close File' menu option is clicked.*/
    void CloseFile();
    /**This slot gets triggered once the 'About' menu option is clicked.*/
    void OpenAbout();
};

#endif // NEOSTUDIO_H
