#include "generalframe.h"

GeneralFrame::GeneralFrame(PakControls* Pak, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_GeneralFrame();
    ui->setupUi(this);

    if(Pak->HasFailed())
    {
        Debug::ConsolePrint("Error! GeneralFrame: couldn't initialize pak file.");
        return;
    }
    paramData = *new QByteArray(Pak->GetParamData(GENERAL));

    InitializeUIElements();
}
void GeneralFrame::InitializeUIElements()
{
    // Now I know this looks bad...
    // I could make an array of Pointers and
    // initialize all of these UI elements in for loops,
    // but idk if that would be better, feedback on that is appreciated.
    IsInitializing = true;
    unsigned char* readParamPtr = (unsigned char*)paramData.constData();

    // Transformations
    ui->TransformIDBox_1->setValue(readParamPtr[0x00]);
    ui->TransformIDBox_2->setValue(readParamPtr[0x01]);
    ui->TransformIDBox_3->setValue(readParamPtr[0x02]);
    ui->TransformIDBox_4->setValue(readParamPtr[0x03]);
    ui->TransformCostBox_1->setValue(readParamPtr[0x04]);
    ui->TransformCostBox_2->setValue(readParamPtr[0x05]);
    ui->TransformCostBox_3->setValue(readParamPtr[0x06]);
    ui->TransformCostBox_4->setValue(readParamPtr[0x07]);

    // Fusions
    ui->FusionIDBox_1->setValue(readParamPtr[0x10]);
    ui->FusionIDBox_2->setValue(readParamPtr[0x11]);
    ui->FusionIDBox_3->setValue(readParamPtr[0x12]);
    ui->FusionCostBox_1->setValue(readParamPtr[0x0A]);
    ui->FusionCostBox_2->setValue(readParamPtr[0x0B]);
    ui->FusionCostBox_3->setValue(readParamPtr[0x0C]);
    FusionType[0] = readParamPtr[0x0D];
    DisplayFusionType((Fusion_Type)FusionType[0], ui->FusionTypeBtn_1);
    FusionType[1] = readParamPtr[0x0E];
    DisplayFusionType((Fusion_Type)FusionType[1], ui->FusionTypeBtn_2);
    FusionType[2] = readParamPtr[0x0F];
    DisplayFusionType((Fusion_Type)FusionType[2], ui->FusionTypeBtn_3);
    ui->PartnerIDBox_1->setValue(readParamPtr[0x13]);
    ui->PartnerIDBox_2->setValue(readParamPtr[0x14]);
    ui->PartnerIDBox_3->setValue(readParamPtr[0x15]);
    ui->PartnerTeamIDBox_1_1->setValue(readParamPtr[0x16]);
    ui->PartnerTeamIDBox_1_2->setValue(readParamPtr[0x17]);
    ui->PartnerTeamIDBox_1_3->setValue(readParamPtr[0x18]);
    ui->PartnerTeamIDBox_1_4->setValue(readParamPtr[0x19]);
    ui->PartnerTeamIDBox_1_5->setValue(readParamPtr[0x1A]);
    ui->PartnerTeamIDBox_1_6->setValue(readParamPtr[0x1B]);
    ui->PartnerTeamIDBox_2_1->setValue(readParamPtr[0x1C]);
    ui->PartnerTeamIDBox_2_2->setValue(readParamPtr[0x1D]);
    ui->PartnerTeamIDBox_2_3->setValue(readParamPtr[0x1E]);
    ui->PartnerTeamIDBox_2_4->setValue(readParamPtr[0x1F]);
    ui->PartnerTeamIDBox_2_5->setValue(readParamPtr[0x20]);
    ui->PartnerTeamIDBox_2_6->setValue(readParamPtr[0x21]);
    ui->PartnerTeamIDBox_3_1->setValue(readParamPtr[0x22]);
    ui->PartnerTeamIDBox_3_2->setValue(readParamPtr[0x23]);
    ui->PartnerTeamIDBox_3_3->setValue(readParamPtr[0x24]);
    ui->PartnerTeamIDBox_3_4->setValue(readParamPtr[0x25]);
    ui->PartnerTeamIDBox_3_5->setValue(readParamPtr[0x26]);
    ui->PartnerTeamIDBox_3_6->setValue(readParamPtr[0x27]);

    // Rushing Techniques
    RushTech[0] = readParamPtr[0x4D];
    DisplayRushTech((Technique)RushTech[0], ui->RushTechBtn_1);
    RushTech[1] = readParamPtr[0x4E];
    DisplayRushTech((Technique)RushTech[1], ui->RushTechBtn_2);
    RushTech[2] = readParamPtr[0x4F];
    DisplayRushTech((Technique)RushTech[2], ui->RushTechBtn_3);
    RushTech[3] = readParamPtr[0x50];
    DisplayRushTech((Technique)RushTech[3], ui->RushTechBtn_4);

    // Counter Techniques
    CounterMove[0] = readParamPtr[0x51];
    DisplayCounterTech((Counter_Move)readParamPtr[0x51], ui->CounterBtn_1);
    CounterMove[1] = readParamPtr[0x51];
    DisplayCounterTech((Counter_Move)readParamPtr[0x52], ui->CounterBtn_2);
    CounterMove[2] = readParamPtr[0x51];
    DisplayCounterTech((Counter_Move)readParamPtr[0x53], ui->CounterBtn_3);

    // Ki
    ui->KiBlastBox_1->setValue(readParamPtr[0x4C]);
    ui->KiBlastBox_2->setValue(readParamPtr[0x57]);
    ui->KiChargeBox_1->setValue(*(int*)(readParamPtr + 0x70));
    ui->KiChargeBox_2->setValue(*(int*)(readParamPtr + 0x74));
    ui->KiChargeBox_3->setValue(*(int*)(readParamPtr + 0x78));
    ui->KiChargeBox_4->setValue(*(int*)(readParamPtr + 0x7C));

    // Collision
    ui->CollisionSpinBox_1->setValue(*(float*)(readParamPtr + 0x40));
    ui->CollisionSpinBox_2->setValue(*(float*)(readParamPtr + 0x44));
    ui->CollisionSpinBox_3->setValue(*(float*)(readParamPtr + 0x48));

    // Flags
    // There are 72 goddamn flags, meaning 72 goddamn QCheckBoxes.
    // Remember that upper talk about pointer arrays?
    // Can't be bothered to manually add all, so this would be an example of it.
    QList<QObject*> FlagCheckBoxes = ui->FlagByteGroup_1->children() +
                                 ui->FlagByteGroup_2->children() +
                                 ui->FlagByteGroup_3->children() +
                                 ui->FlagByteGroup_4->children() +
                                 ui->FlagByteGroup_5->children() +
                                 ui->FlagByteGroup_6->children() +
                                 ui->FlagByteGroup_7->children() +
                                 ui->FlagByteGroup_8->children() +
                                 ui->FlagByteGroup_9->children();
    for(int i=0;i<FlagCheckBoxes.length();i++)
    {
        QStringList flagName = FlagCheckBoxes[i]->objectName().split('_');
        Qt::CheckState bitState;
        bitState = (Qt::CheckState)(2 * FlagByte::Bit((char)(readParamPtr[0x30 + (flagName[1].toUShort() - 1)]), flagName[2].toUShort() - 1));
        ((QCheckBox*)FlagCheckBoxes[i])->setCheckState(bitState);
    }

    // The rest
    ui->ZSearchBox->setCurrentIndex(readParamPtr[0x29]);
    ui->StepInBox->setCurrentIndex(readParamPtr[0x54]);
    ui->AuraColorBox->setCurrentIndex(readParamPtr[0x3F]);
    ui->BlastStockBox->setValue(readParamPtr[0x6C]);
    ui->DragonHomingBox->setValue(readParamPtr[0xA8]);
    ui->VanishingAttackBox->setValue(readParamPtr[0xA9]);
    ui->BlastGaugeBox->setValue(*(int*)(readParamPtr + 0x8C));
    ui->MaxPowDurBox->setValue(*(float*)(readParamPtr + 0x94));
    ui->GravityBox->setValue(*(float*)(readParamPtr + 0x98));
    ui->ChargeBarSpdBox->setValue(*(float*)(readParamPtr + 0xAC));
    ui->DmgMulBox->setValue(*(float*)(readParamPtr + 0xB4));
    ui->TeamGaugeBox->setValue(*(float*)(readParamPtr + 0xB8));

    IsInitializing = false;
}

void GeneralFrame::ChangeID(int ID)
{
    // Why this is a seperate function even though it does the exact same as ChangeAmount() you ask?
    // Well, I am planning on creating a Character Select Dialog, and thus,
    // I will need the IDs be treated seperately from the rest.
    if(paramData.isEmpty())
    {
        QSpinBox* box = (QSpinBox*)sender();
        Debug::ConsolePrint("Error! ChangeID: No file open.");
        box->setValue(0);
        return;
    }
    if(IsInitializing) return;

    // Check which Widget called this function
    // Considering there's 28 ID QSpinBoxes, we need to find
    // the exact Box and it's corresponding parameter in the .pak
    QStringList widgetName = sender()->objectName().split('_');
    unsigned char offset;

    if(widgetName[0] == "TransformIDBox") offset = 0x00 + (widgetName[1].toUShort() - 1);
    else if(widgetName[0] == "FusionIDBox") offset = 0x10 + (widgetName[1].toUShort() - 1);
    else if(widgetName[0] == "PartnerIDBox") offset = 0x13 + (widgetName[1].toUShort() - 1);
    else if(widgetName[0] == "PartnerTeamIDBox") offset = 0x16 + 6 * (widgetName[1].toUShort() - 1) + (widgetName[2].toUShort() - 1);
    else return;

    paramData[offset] = ID;
}

void GeneralFrame::ChangeAmount(int Amount)
{
    if(paramData.isEmpty())
    {
        ((QSpinBox*)sender())->setValue(0);
        Debug::ConsolePrint("Error! ChangeAmount: No file open.");
        return;
    }
    if(IsInitializing) return;

    // This section is to find the location of the
    // corresponding parameter in the .pak file
    QStringList widgetName = sender()->objectName().split('_');
    unsigned char offset;

    // I am YanDev incarnate
    if(widgetName[0] == "TransformCostBox") offset = 0x04 + (widgetName[1].toUShort() - 1);
    else if(widgetName[0] == "FusionCostBox") offset = 0x0A + (widgetName[1].toUShort() - 1);
    else if(widgetName[0] == "KiBlastBox") offset = 0x4C + (0x0B * (widgetName[1].toUShort() - 1));
    else if(widgetName[0] == "BlastStockBox") offset = 0x6C;
    else if(widgetName[0] == "DragonHomingBox") offset = 0xA8;
    else if(widgetName[0] == "VanishingAttackBox") offset = 0xA9;
    else return;

    paramData[offset] = Amount;
}

void GeneralFrame::ChangeIntAmount(int Amount)
{
    if(paramData.isEmpty())
    {
        ((QSpinBox*)sender())->setValue(0);
        Debug::ConsolePrint("Error! ChangeIntAmount: No file open.");
        return;
    }
    if(IsInitializing) return;

    QStringList widgetName = sender()->objectName().split('_');
    unsigned char offset;

    if(widgetName[0] == "BlastGaugeBox") offset = 0x8C;
    else if(widgetName[0] == "KiChargeBox") offset = 0x70 + (widgetName[1].toUShort() - 1) * sizeof(int);
    else return;

    *(int*)(paramData.data() + offset) = Amount;
}

void GeneralFrame::ChangeDoubleAmount(double Amount)
{
    if(paramData.isEmpty())
    {
        ((QSpinBox*)sender())->setValue(0);
        Debug::ConsolePrint("Error! ChangeDoubleAmount: No file open.");
        return;
    }
    if(IsInitializing) return;

    QStringList widgetName = sender()->objectName().split('_');
    unsigned char offset;

    if(widgetName[0] == "CollisionSpinBox") offset = 0x40 + (widgetName[1].toUShort() - 1) * sizeof(int);
    else if(widgetName[0] == "MaxPowDurBox") offset = 0x94;
    else if(widgetName[0] == "GravityBox")
    {
        offset = 0x98;
        if(Amount > MAX_GRAVITY) ui->GravityLbl->setStyleSheet("QLabel { color : red; }");
        else ui->GravityLbl->setStyleSheet("QLabel { color : white; }");
    }
    else if(widgetName[0] == "ChargeBarSpdBox") offset = 0xAC;
    else if(widgetName[0] == "DmgMulBox") offset = 0xB4;
    else if(widgetName[0] == "TeamGaugeBox") offset = 0xB8;
    else return;

    *(float*)(paramData.data() + offset) = (float)Amount;
}

void GeneralFrame::ChangeFlagState(int State)
{
    if(paramData.isEmpty())
    {
        ((QSpinBox*)sender())->setValue(0);
        Debug::ConsolePrint("Error! ChangeFlagState: No file open.");
        return;
    }
    if(IsInitializing) return;

    QStringList widgetName = sender()->objectName().split('_');
    unsigned char byte = 0x30 + (widgetName[1].toUShort() - 1);
    unsigned char bit = widgetName[2].toUShort() - 1;

    FlagByte::SetBit(paramData.data() + byte, bit, (bool)State);
}

void GeneralFrame::ChangeRushTech()
{
    if(paramData.isEmpty())
    {
        Debug::ConsolePrint("Error! ChangeRushTech: No file open.");
        return;
    }
    QPushButton* button = (QPushButton*)sender();
    unsigned char buttonNr = button->objectName().split('_')[1].toInt() - 1;
    // Change currently displayed Rushing Technique
    if(RushTech[buttonNr] >= 3) RushTech[buttonNr] = 0;
    else RushTech[buttonNr]++;
    switch((Technique)RushTech[buttonNr])
    {
        case NO_TECHNIQUE:
        {
            button->setText("No Technique");
            break;
        }
        case HEAVY:
        {
            button->setText("Heavy Finish");
            break;
        }
        case KIAI:
        {
            button->setText("Kiai Cannon");
            break;
        }
        case FLYING_KICKS:
        {
            button->setText("Flying Kicks");
            break;
        }
    }
    if(IsInitializing) return;
    // actually change Rushing Technique
    paramData[0x4D + buttonNr] = RushTech[buttonNr];
}

void GeneralFrame::DisplayRushTech(Technique Type, QPushButton* Button)
{
    if(paramData.isEmpty())
    {
        Debug::ConsolePrint("Error! ChangeRushTech: No file open.");
        return;
    }
    if(Button == nullptr) Button = (QPushButton*)sender();
    // To output the type as the button text
    switch(Type)
    {
        case NO_TECHNIQUE:
        {
            Button->setText("No Technique");
            break;
        }
        case HEAVY:
        {
            Button->setText("Heavy Finish");
            break;
        }
        case KIAI:
        {
            Button->setText("Kiai Cannon");
            break;
        }
        case FLYING_KICKS:
        {
            Button->setText("Flying Kicks");
            break;
        }
    }
}

void GeneralFrame::ChangeCounterTech()
{
    if(paramData.isEmpty())
    {
        Debug::ConsolePrint("Error! ChangeCounterTech: No file open.");
        return;
    }
    QPushButton* button = (QPushButton*)sender();
    unsigned char buttonNr = button->objectName().split('_')[1].toInt() - 1;
    // Change currently displayed Rushing Technique
    if(CounterMove[buttonNr] >= 3) CounterMove[buttonNr] = 0;
    else CounterMove[buttonNr]++;

    switch((Counter_Move)CounterMove[buttonNr])
    {
        case NO_COUNTER:
        {
            button->setText("No Counter");
            break;
        }
        case SMASH:
        {
            button->setText("Smash ");
            break;
        }
        case FEINT:
        {
            button->setText("Feint");
            break;
        }
        case THROW:
        {
            button->setText("Throw");
            break;
        }
    }

    paramData[0x51 + buttonNr] = CounterMove[buttonNr];
}

void GeneralFrame::DisplayCounterTech(Counter_Move Type, QPushButton* Button)
{
    if(paramData.isEmpty())
    {
        Debug::ConsolePrint("Error! ChangeCounterTech: No file open.");
        return;
    }
    if(Button == nullptr) Button = (QPushButton*)sender();
    // To output the type as the button text
    switch(Type)
    {
        case NO_COUNTER:
        {
            Button->setText("No Counter");
            break;
        }
        case SMASH:
        {
            Button->setText("Smash ");
            break;
        }
        case FEINT:
        {
            Button->setText("Feint");
            break;
        }
        case THROW:
        {
            Button->setText("Throw");
            break;
        }
    }
}

void GeneralFrame::ChangeFusionType()
{
    if(paramData.isEmpty())
    {
        Debug::ConsolePrint("Error! ChangeFusionType: No file open.");
        return;
    }
    QPushButton* button = (QPushButton*)sender();
    unsigned char buttonNr = button->objectName().split('_')[1].toInt() - 1;
    // Change currently displayed Fusion Type
    // To output the type as the Button text
    if(FusionType[buttonNr] >= 2) FusionType[buttonNr] = 0;
    else FusionType[buttonNr]++;
    switch((Fusion_Type)FusionType[buttonNr])
    {
        case NO_FUSION:
        {
            button->setText("None");
            break;
        }
        case POTARA:
        {
            button->setText("Potara");
            break;
        }
        case FUSION_DANCE:
        {
            button->setText("Dance");
            break;
        }
    }

    if(IsInitializing) return;

    paramData[0x0D + buttonNr] = FusionType[buttonNr];
}

void GeneralFrame::DisplayFusionType(Fusion_Type Type, QPushButton* Button)
{
    if(paramData.isEmpty())
    {
        Debug::ConsolePrint("Error! ChangeRushTech: No file open.");
        return;
    }
    if(Button == nullptr) Button = (QPushButton*)sender();
    // To output the type as the Button text
    switch(Type)
    {
        case NO_FUSION:
        {
            Button->setText("None");
            break;
        }
        case POTARA:
        {
            Button->setText("Potara");
            break;
        }
        case FUSION_DANCE:
        {
            Button->setText("Dance");
            break;
        }
    }
}

void GeneralFrame::ChangeAuraColor(int Index)
{
    if(paramData.isEmpty())
    {
        ((QComboBox*)sender())->setCurrentIndex(0);
        Debug::ConsolePrint("Error! ChangeAuraColor: No file open.");
        return;
    }
    if(IsInitializing) return;

    paramData[0x3F] = Index;
}

void GeneralFrame::ChangeZSearch(int Index)
{
    if(paramData.isEmpty())
    {
        ((QComboBox*)sender())->setCurrentIndex(0);
        Debug::ConsolePrint("Error! ChangeZSearch: No file open.");
        return;
    }
    if(IsInitializing) return;

    paramData[0x29] = Index;
}

void GeneralFrame::ChangeStepInTech(int Index)
{
    if(paramData.isEmpty())
    {
        ((QComboBox*)sender())->setCurrentIndex(0);
        Debug::ConsolePrint("Error! ChangeStepInTech: No file open.");
        return;
    }
    if(IsInitializing) return;

    paramData[0x54] = Index;
}
