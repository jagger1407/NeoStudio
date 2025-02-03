#ifndef SECTIONSELECTIONDIALOG_H
#define SECTIONSELECTIONDIALOG_H

#include "src/external/qt_includes.h"

#include "ui_sectionselectiondialog.h"
#include "src/options.h"

namespace Ui
{
class SectionSelectionDialog;
}

/**
 * @todo write docs
 */
class SectionSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    static const int ExportAborted = -1;
    static const int ExportAll = -2;

    static int SelectExport(int selectedSection);
private:
    SectionSelectionDialog(QWidget* parent = nullptr);
    QScopedPointer<Ui::SectionSelectionDialog> ui;
    bool finished = false;
    bool exportAll = false;
private slots:
    void ExportClicked();
    void ExportAllClicked();
};

#endif // SECTIONSELECTIONDIALOG_H
