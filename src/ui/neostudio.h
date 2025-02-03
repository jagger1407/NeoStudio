#ifndef NEOSTUDIO_H
#define NEOSTUDIO_H

#include "src/external/qt_includes.h"
#include "src/external/fileparse.h"
#include "src/external/debug.h"
#include "menu/aboutwindow.h"
#include "menu/optiondialog.h"
#include "menu/datselectiondialog.h"

#include "src/pak_filesystem/pakcontrols.h"

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
    explicit NeoStudio(int argc, char* argv[], QWidget* parent = NULL);
    /**Destructor. Idk how to use this, it was automatically generated.*/
    ~NeoStudio() override;
private:

    /**QScopedPointer to access UI Elements.*/
    QScopedPointer<Ui::NeoStudio> ui;

    /**The path to the currently open Pak file.*/
    QString file;
    /**PakControls object to act as an interface between this program and the file itself.*/
    PakControls* pak = NULL;
    /**Initializes the program using the current Pak filepath.*/
    void InitPakFile();
    /**Initializes one specific section using the current Dat filepath.*/
    void InitDatFile();
    /**Checks the UI mode and sets the Stylesheet accordingly.*/
    void ResetUiMode();

    /**All currently implemented editors for Neo Studio.*/
    typedef enum {
        EDITOR_INVALID = -1,
        EDITOR_PARAMETERS,
        //EDITOR_SKILL_LIST,

        EDITOR_COUNT
    } EditorType;

    /**QFrame* array that stores all editors.*/
    QFrame** editors = NULL;
    /**If a singular section was opened, this stores the data.*/
    QByteArray dat;
    /**If a singular section was opened, this stores the type.*/
    SectionOffset datIndex = SECTION_OFFSET_INVALID;

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
    /**Exports the specified section as a standalone file.*/
    void ExportSection();
    /**Imports a section of the .pak as a into the .pak file.*/
    void ImportSection();
    /**Changes the displayed Editor if the user selects a different one from the list.*/
    void SelectedEditorChanged(int editorId);
};

#endif // NEOSTUDIO_H
