#ifndef KIFRAME_H
#define KIFRAME_H

#include "ui_kiframe.h"
#include "src/options.h"
#include "src/external/qt_includes.h"
#include "src/external/debug.h"
#include "src/pak_filesystem/kiparameters.h"
#include "src/pak_filesystem/pakcontrols.h"

namespace Ui
{
class KiFrame;
}

/**
 * @todo write docs
 */
class KiFrame : public QFrame
{
    Q_OBJECT
public:
    /**Constructor. Creates PakControls object and initializes UI with .pak values.*/
    explicit KiFrame(QByteArray Data, QWidget* parent = nullptr);
    /**Pointer used to access UI elements of this window.*/
    Ui_KiFrame* ui;
    /**Pointer used to access Parameters that this QFrame is editing.*/
    KiParameters* kp = nullptr;
    /**Checks the UI mode and sets the Stylesheet accordingly.*/
    void ResetUiMode();
    /**Method to initialize all the UI Elements with their parameter values from the Pak File.*/
    void InitializeUIElements();
private:
    /**Checks to see if the UI is initializing, used to supress slots while initializing.*/
    bool IsInitializing = true;

private slots:
    void QSpinBox_Changed(int NewValue);
    void QDoubleSpinBox_Changed(double NewValue);
    void ComboBox_IndexChanged(int NewIndex);
    void CurrentBlast_IndexChanged(int NewIndex);
    void CheckBox_StateChanged(int NewState);
};

#endif // KIFRAME_H
