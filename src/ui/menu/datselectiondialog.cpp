#include "datselectiondialog.h"

DatSelectionDialog::SelectOption DatSelectionDialog::SelectDat()
{
    DatSelectionDialog window;
    window.setWindowTitle("Pak Subsection was edited");
    window.exec();
    return window.useEdited;
}

DatSelectionDialog::DatSelectionDialog(QWidget* parent) : ui(new Ui::DatSelectionDialog)
{
    ui->setupUi(this);
    this->setParent(parent);
}

void DatSelectionDialog::Edited_Select()
{
    this->useEdited = DATSELECT_EDITED;
    this->close();
}

void DatSelectionDialog::Original_Select()
{
    this->useEdited = DATSELECT_ORIGINAL;
    this->close();
}
