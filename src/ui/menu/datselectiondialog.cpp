#include "datselectiondialog.h"

bool DatSelectionDialog::SelectDat(Options* options)
{
    DatSelectionDialog window(options);
    window.exec();
    return window.useEdited;
}

DatSelectionDialog::DatSelectionDialog(Options* options, QWidget* parent) : op(options), ui(new Ui::DatSelectionDialog)
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
