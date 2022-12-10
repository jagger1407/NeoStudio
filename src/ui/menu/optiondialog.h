#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include "src/external/qt_includes.h"
#include "ui_optiondialog.h"
#include "src/external/debug.h"
#include "src/options.h"

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
    OptionDialog(Options* options);
private:
    QScopedPointer<Ui::OptionDialog> ui;
    Options* options = nullptr;
private slots:
    void DebugEnableCheckState_Changed(int NewState);
    void LoggingMode_IndexChanged(int NewIndex);
    void TooltipColor_IndexChanged(int NewIndex);
    void UiModeBox_IndexChanged(int NewIndex);
    void SaveBtn_Clicked();
    void CancelBtn_Clicked();
};

#endif // OPTIONDIALOG_H
