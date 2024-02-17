#ifndef CHARACTERSELECTIONDIALOG_H
#define CHARACTERSELECTIONDIALOG_H

#include "src/external/qt_includes.h"
#include "ui_characterselectiondialog.h"
#include "src/external/fileparse.h"
#include "src/neo_info.h"
#include "src/options.h"
#include "src/external/debug.h"

namespace Ui
{
class CharacterSelectionDialog;
}

/**
 * @todo write docs
 */
class CharacterSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    CharacterSelectionDialog(QWidget* parent = nullptr);
    unsigned char getSelectedID();
    QListWidgetItem* getSelectedItem();
    QListWidgetItem* getItem(int index);
    bool aborted() { return wasAborted; }

private:

    // Will be part of the options soon
    QString charNamePath = "./assets/char-list.txt";

    Ui_CharacterSelectionDialog* ui;
    QStringList charNames;
    unsigned char selectedID = 0xFF;
    bool wasAborted = true;
    QIcon icons[ROSTER_SIZE];

    void populateList(QString filter = NULL);

private slots:
    void CharacterSelected(QListWidgetItem* item);
    void FilterChanged(QString newFilter);
};

#endif // CHARACTERSELECTIONDIALOG_H
