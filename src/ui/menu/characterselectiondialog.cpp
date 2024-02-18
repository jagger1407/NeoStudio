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

    if(!FileParse::DoesFileExist(this->charNamePath))
    {
        Debug::Log("Character Name List (" + this->charNamePath + ") doesn't exist.", Debug::ERROR);
    }

    charNames = FileParse::ReadLines(this->charNamePath);
    if(charNames.length() != ROSTER_SIZE)
    {
        Debug::Log("Length of Character Name List (" + this->charNamePath + ") doesn't match up with ROSTER_SIZE.\n" \
        "Name List: " + QString::number(charNames.length()) + "\tRoster Size: " + QString::number(ROSTER_SIZE), Debug::ERROR);
        return;
    }
    for(int i=0;i<ROSTER_SIZE;i++)
    {
        if(charNames[i].contains('|'))
            charNames[i].replace('|', "\n");

        icons[i] = QIcon("./assets/character_icons/" + QString::number(i) + ".png");
    }


    ui->CharacterList->setIconSize(QSize(64, 64));

    populateList();
    Debug::Log("CharacterSelectionDialog constructed.", Debug::INFO);
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
            item->setIcon(icons[i]);
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
                item->setIcon(icons[i]);
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

