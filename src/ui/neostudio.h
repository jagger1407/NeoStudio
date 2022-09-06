#ifndef NEOSTUDIO_H
#define NEOSTUDIO_H

#include "src/external/qt_includes.h"
#include "src/external/debug.h"
#include "menu/aboutwindow.h"
#include "menu/optiondialog.h"
// Parameter Tabs
#include "src/ui/paramSections/generalframe.h"

#include "src/external/fileparse.h"

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

    /**Constructor. Creates the main Neo Studio window.*/
    explicit NeoStudio(QWidget* parent = nullptr);
    /**Destructor. Idk how to use this, it was automatically generated.*/
    ~NeoStudio() override;
private:
    /**QScopedPointer to access UI Elements.*/
    QScopedPointer<Ui::NeoStudio> ui;
    /**The UI for the General Parameter editing tab.*/
    GeneralFrame* generalWindow = nullptr;
    /**The path to the currently open Pak file.*/
    QString file;
    /**PakControls object to act as an interface between this program and the file itself.*/
    PakControls* pak = nullptr;
    /**Initializes the program using the current Pak filepath.*/
    void InitFile();
    /**Checks the UI mode and sets the Stylesheet accordingly.*/
    void ResetUiMode();
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
     /**This slot gets triggered once the 'Options' menu option is clicked.*/
    void OpenOptions();
};

#endif // NEOSTUDIO_H
