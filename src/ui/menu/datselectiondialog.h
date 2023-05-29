#ifndef DATSELECTIONDIALOG_H
#define DATSELECTIONDIALOG_H

#include "src/external/qt_includes.h"
#include "src/options.h"
#include "ui_datselectiondialog.h"

namespace Ui
{
class DatSelectionDialog;
}

/**
 * @todo write docs
 */
class DatSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    /**false = original, true = edited*/
    static bool SelectDat(Options* options);
private:
    DatSelectionDialog(Options* options, QWidget* parent = nullptr);
    Options* op = nullptr;
    QScopedPointer<Ui::DatSelectionDialog> ui;

    bool useEdited = false;
private slots:
    void Edited_Select();
    void Original_Select();
};

#endif // DATSELECTIONDIALOG_H
