#include "sectionselectiondialog.h"

SectionSelectionDialog::SectionSelectionDialog(QWidget* parent)
    : ui(new Ui::SectionSelectionDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Select Pak Section");

    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));

    QStringList sections = FileParse::ReadLines(g_Options.sectionNameFile);
    for(QString section : sections) {
        ui->SectionComboBox->addItem(section);
    }
}

void SectionSelectionDialog::ExportClicked()
{
    finished = true;
    exportAll = false;
    this->close();
}
void SectionSelectionDialog::ExportAllClicked()
{
    finished = true;
    exportAll = true;
    this->close();
}

int SectionSelectionDialog::SelectExport(int selectedSection)
{
    SectionSelectionDialog window;
    window.ui->SectionComboBox->setCurrentIndex(selectedSection);
    window.exec();
    if(!window.finished) return ExportAborted;
    if(window.exportAll) return ExportAll;
    return window.ui->SectionComboBox->currentIndex();
}
