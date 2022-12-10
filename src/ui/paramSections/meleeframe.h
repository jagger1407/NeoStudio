#ifndef MELEEFRAME_H
#define MELEEFRAME_H

#include "ui_meleeframe.h"
#include "src/options.h"
#include "src/external/qt_includes.h"
#include "src/external/debug.h"
#include "src/pak_filesystem/meleeparameters.h"
#include "src/pak_filesystem/pakcontrols.h"

namespace Ui
{
class MeleeFrame;
}

/**
 * @todo write docs
 */
class MeleeFrame : public QFrame
{
    Q_OBJECT
public:
    /**Constructor. Creates PakControls object and initializes UI with .pak values.*/
    explicit MeleeFrame(PakControls* Pak, Options* options, QWidget* parent = nullptr);
    /**Pointer used to access UI elements of this window.*/
    Ui_MeleeFrame* ui;
    /**Pointer used to access Parameters that this QFrame is editing.*/
    MeleeParameters* mp = nullptr;

    Options* options = nullptr;
    /**Checks the UI mode and sets the Stylesheet accordingly.*/
    void ResetUiMode();
private:
    /**Checks to see if the UI is initializing, used to supress slots while initializing.*/
    bool IsInitializing = true;
    /**Method to initialize all the UI Elements with their parameter values from the Pak File.*/
    void InitializeUIElements();

private slots:
    void QSpinBox_Changed(int NewValue);
    void QDoubleSpinBox_Changed(double NewValue);
    void ComboBox_IndexChanged(int NewIndex);
    void CurrentAttack_IndexChanged(int NewIndex);
    void CheckBox_StateChanged(int NewState);
};

#endif // MELEEFRAME_H
