#include "characterselectiondialog.h"
#include "ui_characterselectiondialog.h"

CharacterSelectionDialog::CharacterSelectionDialog(QWidget* parent)
    : ui(new Ui::CharacterSelectionDialog)
{
    ui->setupUi(this);
    this->setParent(parent);
    this->setWindowTitle("Choose a Character...");
    this->setWindowIcon(QIcon("./assets/CharacterSelectionIcon.png"));

    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));

    charNames = FileParse::ReadLines("./assets/char-list.txt");
    for(int i=0;i<charNames.length();i++)
        if(charNames[i].contains('|'))
            charNames[i].replace('|', "\n");

    ui->CharacterList->setIconSize(QSize(64, 64));

    populateList();
}

unsigned char CharacterSelectionDialog::getSelectedID()
{
    return selectedID;
}

QListWidgetItem* CharacterSelectionDialog::getSelectedItem()
{
    return ui->CharacterList->selectedItems()[0];
}

QListWidgetItem * CharacterSelectionDialog::getItem(int index)
{
    if(index >= ROSTER_SIZE) return ui->CharacterList->item(ui->CharacterList->count()-1);
    return ui->CharacterList->item(index);
}

void CharacterSelectionDialog::populateList(QString filter)
{
    if(filter == NULL || filter.isEmpty())
    {
        for(int i=0;i<ROSTER_SIZE;i++)
        {
            QListWidgetItem* item = new QListWidgetItem("ID: " + QString::number(i) + "\n" + charNames[i]);
            item->setIcon(QIcon("./assets/character_icons/" + QString::number(i) + ".png"));
            ui->CharacterList->addItem(item);
        }
    }
    else
    {
        for(int i=0;i<ROSTER_SIZE;i++)
        {
            if(charNames[i].contains(filter, Qt::CaseInsensitive))
            {
                QListWidgetItem* item = new QListWidgetItem("ID: " + QString::number(i) + "\n" + charNames[i]);
                item->setIcon(QIcon("./assets/character_icons/" + QString::number(i) + ".png"));
                ui->CharacterList->addItem(item);
            }
        }
    }
    QListWidgetItem* noChar = new QListWidgetItem("ID: 255\nNo Character");
    noChar->setIcon(QIcon("./assets/character_icons/255.png"));
    ui->CharacterList->addItem(noChar);
}

void CharacterSelectionDialog::CharacterSelected(QListWidgetItem* item)
{
    selectedID = ui->CharacterList->row(item);
    if(selectedID >= ROSTER_SIZE) selectedID = 0xFF;

    wasAborted = false;

    this->close();
}

void CharacterSelectionDialog::FilterChanged(QString newFilter)
{
    ui->CharacterList->clear();

    populateList(newFilter);
}

