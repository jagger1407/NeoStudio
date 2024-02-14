#include "datselectiondialog.h"

bool DatSelectionDialog::SelectDat()
{
    DatSelectionDialog window;
    window.exec();
    return window.useEdited;
}

DatSelectionDialog::DatSelectionDialog(QWidget* parent) : ui(new Ui::DatSelectionDialog)
{
    ui->setupUi(this);
}

void DatSelectionDialog::Edited_Select()
{
    this->useEdited = true;
    this->close();
}

void DatSelectionDialog::Original_Select()
{
    this->useEdited = false;
    this->close();
}
