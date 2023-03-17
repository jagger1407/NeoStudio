#ifndef NEOSTUDIO_H
#define NEOSTUDIO_H

#include "src/external/qt_includes.h"
#include "src/external/fileparse.h"
#include "src/external/debug.h"
#include "menu/aboutwindow.h"
#include "menu/optiondialog.h"
// Parameter Tabs
#include "src/ui/paramSections/generalframe.h"
#include "src/ui/paramSections/meleeframe.h"
#include "src/ui/paramSections/kiframe.h"

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
    explicit NeoStudio(int argc, char* argv[], QWidget* parent = nullptr);
    /**Destructor. Idk how to use this, it was automatically generated.*/
    ~NeoStudio() override;
private:
    QString filenameDat[NEXT] = {
        "/017_character_param.dat",
        "/018_character_melee_param.dat",
        "/019_character_ki_blast_param.dat",
        "/020_character_movement_param.dat"
    };

    /**QScopedPointer to access UI Elements.*/
    QScopedPointer<Ui::NeoStudio> ui;
    /**The UI for the General Parameter editing tab.*/
    GeneralFrame* generalWindow = nullptr;
    /**The UI for the Melee Parameter editing tab.*/
    MeleeFrame* meleeWindow = nullptr;
    /**The UI for the Ki Blast Parameter editing tab.*/
    KiFrame* kiWindow = nullptr;
    /**The path to the currently open Pak file.*/
    QString file;
    /**PakControls object to act as an interface between this program and the file itself.*/
    PakControls* pak = nullptr;
    Options* options = nullptr;
    /**Initializes the program using the current Pak filepath.*/
    void InitPakFile();
    /**Initializes one specific section using the current Dat filepath.*/
    void InitDatFile();
    /**Checks the UI mode and sets the Stylesheet accordingly.*/
    void ResetUiMode();
    /**If .dat file was opened, this shows which parameter type the file is.*/
    ParameterType datIndex = PARAM_TYPE_INVALID;
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
    /**Exports the specified parameter type as a .dat file.*/
    void ExportDat();
    /**Imports a .dat file as a parameter section within a .pak file.*/
    void ImportDat();
};

#endif // NEOSTUDIO_H
