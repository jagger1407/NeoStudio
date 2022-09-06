#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include "src/external/qt_includes.h"
#include "ui_optiondialog.h"
#include "src/external/debug.h"
#include "src/external/optionprocessing.h"

namespace Ui
{
class OptionDialog;
}

/**
 * @todo write docs
 */
class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    OptionDialog();
private:
    QScopedPointer<Ui::OptionDialog> ui;
private slots:
    void DebugEnableCheckState_Changed(int NewState);
    void LoggingMode_IndexChanged(int NewIndex);
    void TooltipColor_IndexChanged(int NewIndex);
    void SaveBtn_Clicked();
    void CancelBtn_Clicked();
};

#endif // OPTIONDIALOG_H
