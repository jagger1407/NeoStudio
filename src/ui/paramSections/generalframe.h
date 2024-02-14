#ifndef GENERALFRAME_H
#define GENERALFRAME_H

#include "ui_generalframe.h"
#include "src/options.h"
#include "src/external/qt_includes.h"
#include "src/external/debug.h"
#include "src/ui/menu/characterselectiondialog.h"
#include "src/pak_filesystem/generalparameters.h"
#include "src/pak_filesystem/pakcontrols.h"


namespace Ui
{
class GeneralFrame;
}

/**
 * The General Parameter Window.
 */
class GeneralFrame : public QFrame
{
    Q_OBJECT
public:
    /**Constructor. Creates PakControls object and initializes UI with .pak values.*/
    explicit GeneralFrame(QByteArray Data, QWidget* parent = nullptr);
    /**Pointer used to access UI elements of this window.*/
    Ui_GeneralFrame* ui;
    /**Pointer used to access Parameters that this QFrame is editing.*/
    GeneralParameters* gp = nullptr;
    /**Checks the UI mode and sets the Stylesheet accordingly.*/
    void ResetUiMode();
    /**Method to initialize all the UI Elements with their parameter values from the Pak File.*/
    void InitializeUIElements();
private:
    QString rushStr[4] = {
                "Heavy Finish",
                "Kiai Cannon",
                "Flying Kicks",
                "None"
    };
    QString counterStr[5] = {
                "No Counter",
                "Smash",
                "Vanish",
                "Throw",
                "Sway"
    };
    QString fusionStr[3] = {
                "None",
                "Dance",
                "Potara"
    };
    int rush[4] = { 0, 0, 0, 0 };
    int counter[3] = { 0, 0, 0 };
    int fusion[3] = { 0, 0, 0 };

    Options* options = nullptr;
    /**Checks to see if the UI is initializing, used to supress slots while initializing.*/
    bool IsInitializing = false;
    /**Method to Change the parameter value when clicking a button, created to keep the slots clean.*/
    void ButtonChange(QPushButton* Button);
    /**Method to get the parameter value each button represents, created to keep InitializeUIElements clean.*/
    void ButtonValueGet(QPushButton* Button);
private slots:
    /**This slot gets triggered everytime the value of a QSpinBox changes.*/
    void QSpinBox_Changed(int NewValue);
    /**This slot gets triggered everytime the value of a QDoubleSpinBox changes.*/
    void QDoubleSpinBox_Changed(double NewValue);
    /**This slot gets triggered everytime the CheckState of a QCheckBox changes.*/
    void Flag_Changed(int NewValue);
    /**This slot gets triggered everytime a Button is clicked.*/
    void Button_Clicked();
    void Character_Selected();
    /**This slot gets triggered everytime the selection of a QComboBox changes.*/
    void ComboBox_IndexChanged(int NewValue);
};

#endif // GENERALFRAME_H
