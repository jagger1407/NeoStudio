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

    typedef enum {
        DATSELECT_ABORT,
        DATSELECT_ORIGINAL,
        DATSELECT_EDITED
    } SelectOption;

    /** Opens the Dat Selection Dialog
     */
    static SelectOption SelectDat();
private:
    DatSelectionDialog(QWidget* parent = nullptr);
    QScopedPointer<Ui::DatSelectionDialog> ui;

    SelectOption useEdited = DATSELECT_ABORT;
private slots:
    void Edited_Select();
    void Original_Select();
};

#endif // DATSELECTIONDIALOG_H
