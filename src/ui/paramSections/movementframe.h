#ifndef MOVEMENTFRAME_H
#define MOVEMENTFRAME_H

#include "ui_movementframe.h"
#include "src/options.h"
#include "src/external/qt_includes.h"
#include "src/external/debug.h"

#include "src/pak_filesystem/movementparameters.h"

namespace Ui
{
class MovementFrame;
}

/**
 * @todo write docs
 */
class MovementFrame : public QFrame
{
    Q_OBJECT

public:
    /**
     * @todo write docs
     */
    MovementFrame(QByteArray Data, QWidget* parent = nullptr);
    /**Pointer used to access UI elements of this window.*/
    Ui_MovementFrame* ui;
    MovementParameters* mp = nullptr;
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
};

#endif // MOVEMENTFRAME_H
