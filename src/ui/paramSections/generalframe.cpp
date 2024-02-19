#include "generalframe.h"

GeneralFrame::GeneralFrame(QByteArray Data, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_GeneralFrame();
    ui->setupUi(this);

    gp = new GeneralParameters(Data);

    #if 1 // Passing the gp Object all UI Elements
    gp->parameter[GeneralParameters::Transform].UiElement = ui->TransformBtn_1;
    gp->parameter[GeneralParameters::Transform+1].UiElement = ui->TransformBtn_2;
    gp->parameter[GeneralParameters::Transform+2].UiElement = ui->TransformBtn_3;
    gp->parameter[GeneralParameters::Transform+3].UiElement = ui->TransformBtn_4;
    gp->parameter[GeneralParameters::TransformCost].UiElement = ui->TransformCostBox_1;
    gp->parameter[GeneralParameters::TransformCost+1].UiElement = ui->TransformCostBox_2;
    gp->parameter[GeneralParameters::TransformCost+2].UiElement = ui->TransformCostBox_3;
    gp->parameter[GeneralParameters::TransformCost+3].UiElement = ui->TransformCostBox_4;
    gp->parameter[GeneralParameters::Unk_0x8].UiElement = ui->SpinBox_Unk_0x8;
    gp->parameter[GeneralParameters::Unk_0x9].UiElement = ui->SpinBox_Unk_0x9;
    gp->parameter[GeneralParameters::FusionCost].UiElement = ui->FusionCostBox_1;
    gp->parameter[GeneralParameters::FusionCost+1].UiElement = ui->FusionCostBox_2;
    gp->parameter[GeneralParameters::FusionCost+2].UiElement = ui->FusionCostBox_3;
    gp->parameter[GeneralParameters::FusionType].UiElement = ui->FusionTypeBtn_1;
    gp->parameter[GeneralParameters::FusionType+1].UiElement = ui->FusionTypeBtn_2;
    gp->parameter[GeneralParameters::FusionType+2].UiElement = ui->FusionTypeBtn_3;
    gp->parameter[GeneralParameters::FusionCharID].UiElement = ui->FusionBtn_1;
    gp->parameter[GeneralParameters::FusionCharID+1].UiElement = ui->FusionBtn_2;
    gp->parameter[GeneralParameters::FusionCharID+2].UiElement = ui->FusionBtn_3;
    gp->parameter[GeneralParameters::FusionPartnerID].UiElement = ui->FusionPartnerBtn_1;
    gp->parameter[GeneralParameters::FusionPartnerID+1].UiElement = ui->FusionPartnerBtn_2;
    gp->parameter[GeneralParameters::FusionPartnerID+2].UiElement = ui->FusionPartnerBtn_3;
    gp->parameter[GeneralParameters::FusionTeamID].UiElement = ui->FusionTeamBtn_1_1;
    gp->parameter[GeneralParameters::FusionTeamID+1].UiElement = ui->FusionTeamBtn_1_2;
    gp->parameter[GeneralParameters::FusionTeamID+2].UiElement = ui->FusionTeamBtn_1_3;
    gp->parameter[GeneralParameters::FusionTeamID+3].UiElement = ui->FusionTeamBtn_1_4;
    gp->parameter[GeneralParameters::FusionTeamID+4].UiElement = ui->FusionTeamBtn_1_5;
    gp->parameter[GeneralParameters::FusionTeamID+5].UiElement = ui->FusionTeamBtn_1_6;
    gp->parameter[GeneralParameters::FusionTeamID+6].UiElement = ui->FusionTeamBtn_2_1;
    gp->parameter[GeneralParameters::FusionTeamID+7].UiElement = ui->FusionTeamBtn_2_2;
    gp->parameter[GeneralParameters::FusionTeamID+8].UiElement = ui->FusionTeamBtn_2_3;
    gp->parameter[GeneralParameters::FusionTeamID+9].UiElement = ui->FusionTeamBtn_2_4;
    gp->parameter[GeneralParameters::FusionTeamID+10].UiElement = ui->FusionTeamBtn_2_5;
    gp->parameter[GeneralParameters::FusionTeamID+11].UiElement = ui->FusionTeamBtn_2_6;
    gp->parameter[GeneralParameters::FusionTeamID+12].UiElement = ui->FusionTeamBtn_3_1;
    gp->parameter[GeneralParameters::FusionTeamID+13].UiElement = ui->FusionTeamBtn_3_2;
    gp->parameter[GeneralParameters::FusionTeamID+14].UiElement = ui->FusionTeamBtn_3_3;
    gp->parameter[GeneralParameters::FusionTeamID+15].UiElement = ui->FusionTeamBtn_3_4;
    gp->parameter[GeneralParameters::FusionTeamID+16].UiElement = ui->FusionTeamBtn_3_5;
    gp->parameter[GeneralParameters::FusionTeamID+17].UiElement = ui->FusionTeamBtn_3_6;
    gp->parameter[GeneralParameters::Unk_0x28].UiElement = ui->SpinBox_Unk_0x28;
    gp->parameter[GeneralParameters::ZSearch].UiElement = ui->ZSearchBox;
    gp->parameter[GeneralParameters::ZSearch+1].UiElement = ui->ZSearchBox_2;
    gp->parameter[GeneralParameters::ZSearch+2].UiElement = ui->ZSearchBox_3;
    gp->parameter[GeneralParameters::ZSearch+3].UiElement = ui->ZSearchBox_4;
    gp->parameter[GeneralParameters::ZSearch+4].UiElement = ui->ZSearchBox_5;
    gp->parameter[GeneralParameters::ZSearch+5].UiElement = ui->ZSearchBox_6;
    gp->parameter[GeneralParameters::Unk_0x2F].UiElement = ui->SpinBox_Unk_0x2F;
    gp->parameter[GeneralParameters::FlagGroup].UiElement = ui->FlagGroup_1;
    gp->parameter[GeneralParameters::FlagGroup+1].UiElement = ui->FlagGroup_2;
    gp->parameter[GeneralParameters::FlagGroup+2].UiElement = ui->FlagGroup_3;
    gp->parameter[GeneralParameters::GreatApeMode].UiElement = ui->Flag_GreatApeMode;
    gp->parameter[GeneralParameters::AuraColor].UiElement = ui->AuraColorBox;
    gp->parameter[GeneralParameters::Collision].UiElement = ui->CollisionSpinBox_1;
    gp->parameter[GeneralParameters::Collision+1].UiElement = ui->CollisionSpinBox_2;
    gp->parameter[GeneralParameters::Collision+2].UiElement = ui->CollisionSpinBox_3;
    gp->parameter[GeneralParameters::KiBlastAmount].UiElement = ui->KiBlastBox;
    gp->parameter[GeneralParameters::RushingTechnique].UiElement = ui->RushTechBtn_1;
    gp->parameter[GeneralParameters::RushingTechnique+1].UiElement = ui->RushTechBtn_2;
    gp->parameter[GeneralParameters::RushingTechnique+2].UiElement = ui->RushTechBtn_3;
    gp->parameter[GeneralParameters::RushingTechnique+3].UiElement = ui->RushTechBtn_4;
    gp->parameter[GeneralParameters::CounterMove].UiElement = ui->CounterBtn_1;
    gp->parameter[GeneralParameters::CounterMove+1].UiElement = ui->CounterBtn_2;
    gp->parameter[GeneralParameters::CounterMove+2].UiElement = ui->CounterBtn_3;
    gp->parameter[GeneralParameters::StepInMove].UiElement = ui->StepInBox;
    gp->parameter[GeneralParameters::StepInMove+1].UiElement = ui->StepInBox_2;
    gp->parameter[GeneralParameters::StepInMove+2].UiElement = ui->StepInBox_3;
    gp->parameter[GeneralParameters::ChargedBlastAmount].UiElement = ui->KiBlastChargedBox;
    gp->parameter[GeneralParameters::Unk_0x58].UiElement = ui->SpinBox_Unk_0x58;
    gp->parameter[GeneralParameters::Unk_0x5C].UiElement = ui->SpinBox_Unk_0x5C;
    gp->parameter[GeneralParameters::Unk_0x60].UiElement = ui->SpinBox_Unk_0x60;
    gp->parameter[GeneralParameters::Unk_0x64].UiElement = ui->SpinBox_Unk_0x64;
    gp->parameter[GeneralParameters::Unk_0x68].UiElement = ui->SpinBox_Unk_0x68;
    gp->parameter[GeneralParameters::BlastStockAmount].UiElement = ui->BlastStockBox;
    gp->parameter[GeneralParameters::KiChargeSpeed].UiElement = ui->KiChargeBox;
    gp->parameter[GeneralParameters::KiChargeSpeedWater].UiElement = ui->KiChargeWaterBox;
    gp->parameter[GeneralParameters::BaseKiRegen].UiElement = ui->BaseKiRegenBox;
    gp->parameter[GeneralParameters::CounterKi].UiElement = ui->CounterKiBox;
    gp->parameter[GeneralParameters::Unk_0x80].UiElement = ui->SpinBox_Unk_0x80;
    gp->parameter[GeneralParameters::PowerGuardKiCost].UiElement = ui->PowerGuardKiBox;
    gp->parameter[GeneralParameters::Unk_0x88].UiElement = ui->SpinBox_Unk_0x88;
    gp->parameter[GeneralParameters::BlastGaugeSpeed].UiElement = ui->BlastGaugeBox;
    gp->parameter[GeneralParameters::BlueKiChargeSpeed].UiElement = ui->BlueKiChargeBox;
    gp->parameter[GeneralParameters::MaxPowerModeDuration].UiElement = ui->MaxPowDurBox;
    gp->parameter[GeneralParameters::Gravity].UiElement = ui->GravityBox;
    gp->parameter[GeneralParameters::Unk_0x9C].UiElement = ui->DblBox_Unk_0x9C;
    gp->parameter[GeneralParameters::Unk_0xA0].UiElement = ui->DblBox_Unk_0xA0;
    gp->parameter[GeneralParameters::Unk_0xA4].UiElement = ui->DblBox_Unk_0xA4;
    gp->parameter[GeneralParameters::MaxDragonSmashes].UiElement = ui->DragonHomingBox;
    gp->parameter[GeneralParameters::MaxVanishingAttacks].UiElement = ui->VanishingAttackBox;
    gp->parameter[GeneralParameters::Unk_0xAA].UiElement = ui->SpinBox_Unk_0xAA;
    gp->parameter[GeneralParameters::MeleeChargeSpeed].UiElement = ui->ChargeBarSpdBox;
    gp->parameter[GeneralParameters::Unk_0xB0].UiElement = ui->DblBox_Unk_0xB0;
    gp->parameter[GeneralParameters::DamageMultiplier].UiElement = ui->DmgMulBox;
    gp->parameter[GeneralParameters::SwitchRegenSpeed].UiElement = ui->TeamGaugeBox;
    gp->parameter[GeneralParameters::Unk_0xBC].UiElement = ui->SpinBox_Unk_0xBC_1;
    gp->parameter[GeneralParameters::Unk_0xBC+1].UiElement = ui->SpinBox_Unk_0xBC_2;
    gp->parameter[GeneralParameters::Unk_0xBC+2].UiElement = ui->SpinBox_Unk_0xBC_3;
    gp->parameter[GeneralParameters::Unk_0xBF].UiElement = ui->SpinBox_Unk_0xBF_1;
    gp->parameter[GeneralParameters::Unk_0xBF+1].UiElement = ui->SpinBox_Unk_0xBF_2;
    gp->parameter[GeneralParameters::Unk_0xBF+2].UiElement = ui->SpinBox_Unk_0xBF_3;
    gp->parameter[GeneralParameters::Unk_0xC2].UiElement = ui->SpinBox_Unk_0xC2_1;
    gp->parameter[GeneralParameters::Unk_0xC2+1].UiElement = ui->SpinBox_Unk_0xC2_2;
    gp->parameter[GeneralParameters::Unk_0xC2+2].UiElement = ui->SpinBox_Unk_0xC2_3;
    gp->parameter[GeneralParameters::Unk_0xC2].UiElement = ui->SpinBox_Unk_0xC2_1;
    gp->parameter[GeneralParameters::Unk_0xC2+1].UiElement = ui->SpinBox_Unk_0xC2_2;
    gp->parameter[GeneralParameters::Unk_0xC2+2].UiElement = ui->SpinBox_Unk_0xC2_3;
    gp->parameter[GeneralParameters::Unk_0xC5].UiElement = ui->SpinBox_Unk_0xC5_1;
    gp->parameter[GeneralParameters::Unk_0xC5+1].UiElement = ui->SpinBox_Unk_0xC5_2;
    gp->parameter[GeneralParameters::Unk_0xC5+2].UiElement = ui->SpinBox_Unk_0xC5_3;
    gp->parameter[GeneralParameters::Unk_0xCF].UiElement = ui->SpinBox_Unk_0xCF_1;
    gp->parameter[GeneralParameters::Unk_0xCF+1].UiElement = ui->SpinBox_Unk_0xCF_2;
    gp->parameter[GeneralParameters::Unk_0xCF+2].UiElement = ui->SpinBox_Unk_0xCF_3;
    #endif

    InitializeUIElements();
    ResetUiMode();
    Debug::Log("GeneralFrame successfully constructed.", Debug::INFO);
}
void GeneralFrame::InitializeUIElements()
{
    IsInitializing = true;

    QList<QLabel*> labels = this->findChildren<QLabel*>();
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();

    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(g_Options.GetStyledTooltip(lbl->toolTip()));
    }
    for(QSpinBox* sBox : spinBoxes)
    {
        if(sBox->maximum() > 255) sBox->setValue(gp->GetIntParameter(sBox));
        else sBox->setValue(gp->GetUByteParameter(sBox));
    }
    for(QDoubleSpinBox* dsBox : dblSpinBoxes)
    {
        dsBox->setValue(gp->GetFloatParameter(dsBox));
    }
    for(QCheckBox* flag : flagBoxes)
    {
        if(!flag->toolTip().isEmpty()) flag->setToolTip(g_Options.GetStyledTooltip(flag->toolTip()));
        flag->setCheckState((Qt::CheckState)(gp->GetFlagParameter(flag) << 1));
    }
    for(QPushButton* btn : buttons)
    {
        QString btnName = btn->objectName();
        ButtonValueGet(btn);
    }
    for(QComboBox* cbBox : comboBoxes)
    {
        if(cbBox->objectName() == "AuraColorBox")
            cbBox->objectName();
        cbBox->setCurrentIndex(gp->GetUByteParameter(cbBox));
    }

    IsInitializing = false;
}
void GeneralFrame::QSpinBox_Changed(int NewValue)
{
    if(IsInitializing || gp == nullptr) return;

    QSpinBox* spinBox = (QSpinBox*)sender();
    if(spinBox->maximum() > 255)
        gp->SetIntParameter(spinBox, NewValue);
    else
        gp->SetUByteParameter(spinBox, NewValue);
}
void GeneralFrame::QDoubleSpinBox_Changed(double NewValue)
{
    if(IsInitializing || gp == nullptr) return;

    QDoubleSpinBox* dblSpinBox = (QDoubleSpinBox*)sender();
    gp->SetFloatParameter(dblSpinBox, (float)NewValue);
}
void GeneralFrame::Button_Clicked()
{
    if(IsInitializing || gp == nullptr) return;

    QPushButton* button = (QPushButton*)sender();
    ButtonChange(button);
}

void GeneralFrame::Character_Selected()
{
    if(IsInitializing || gp == nullptr) return;

    QPushButton* button = (QPushButton*)sender();
    CharacterSelectionDialog dialog;
    dialog.exec();
    if(dialog.aborted()) return;
    gp->SetUByteParameter(button, dialog.getSelectedID());
    button->setIcon(dialog.getSelectedItem()->icon());
    if(!button->objectName().contains("FusionTeamBtn"))
    {
        button->setText(dialog.getSelectedItem()->text());
    }
}

void GeneralFrame::ComboBox_IndexChanged(int NewValue)
{
    if(IsInitializing || gp == nullptr) return;

    gp->SetUByteParameter((QComboBox*)sender(), NewValue);
}
void GeneralFrame::Flag_Changed(int NewValue)
{
    if(IsInitializing || gp == nullptr) return;

    gp->SetFlagParameter((QCheckBox*)sender(), NewValue);
}
void GeneralFrame::ButtonChange(QPushButton* Button)
{
    int curBtn = -1;
    if(Button == ui->RushTechBtn_1) curBtn = 0;
    else if(Button == ui->RushTechBtn_2) curBtn = 1;
    else if(Button == ui->RushTechBtn_3) curBtn = 2;
    else if(Button == ui->RushTechBtn_4) curBtn = 3;
    else if(Button == ui->CounterBtn_1) curBtn = 4;
    else if(Button == ui->CounterBtn_2) curBtn = 5;
    else if(Button == ui->CounterBtn_3) curBtn = 6;
    else if(Button == ui->FusionTypeBtn_1) curBtn = 7;
    else if(Button == ui->FusionTypeBtn_2) curBtn = 8;
    else if(Button == ui->FusionTypeBtn_3) curBtn = 9;

    if(curBtn == -1) return;

    if(curBtn < 4)
    {
        if(rush[curBtn] < 3) rush[curBtn]++;
        else rush[curBtn] = 0;
        Button->setText(rushStr[rush[curBtn]]);
        gp->SetUByteParameter(Button, rush[curBtn]);
    }
    else if(curBtn < 7)
    {
        curBtn -= 4;
        if(counter[curBtn] < 4) counter[curBtn]++;
        else counter[curBtn] = 0;
        Button->setText(counterStr[counter[curBtn]]);
        gp->SetUByteParameter(Button, counter[curBtn]);
    }
    else if(curBtn < 10)
    {
        curBtn -= 7;
        if(fusion[curBtn] < 2) fusion[curBtn]++;
        else fusion[curBtn] = 0;
        Button->setText(fusionStr[fusion[curBtn]]);
        gp->SetUByteParameter(Button, fusion[curBtn]);
    }
}
void GeneralFrame::ButtonValueGet(QPushButton* Button)
{
    int curBtn = -1;

    QString btnName = Button->objectName();
    if(Button == ui->RushTechBtn_1) curBtn = 0;
    else if(Button == ui->RushTechBtn_2) curBtn = 1;
    else if(Button == ui->RushTechBtn_3) curBtn = 2;
    else if(Button == ui->RushTechBtn_4) curBtn = 3;
    else if(Button == ui->CounterBtn_1) curBtn = 4;
    else if(Button == ui->CounterBtn_2) curBtn = 5;
    else if(Button == ui->CounterBtn_3) curBtn = 6;
    else if(Button == ui->FusionTypeBtn_1) curBtn = 7;
    else if(Button == ui->FusionTypeBtn_2) curBtn = 8;
    else if(Button == ui->FusionTypeBtn_3) curBtn = 9;

    else if(Button == ui->TransformBtn_1 ||
            Button == ui->TransformBtn_2 ||
            Button == ui->TransformBtn_3 ||
            Button == ui->TransformBtn_4 ||
            Button == ui->FusionBtn_1 ||
            Button == ui->FusionBtn_2 ||
            Button == ui->FusionBtn_3 ||
            Button == ui->FusionPartnerBtn_1 ||
            Button == ui->FusionPartnerBtn_2 ||
            Button == ui->FusionPartnerBtn_3 )
    {
        curBtn = 10;
    }
    else if(Button == ui->FusionTeamBtn_1_1 ||
            Button == ui->FusionTeamBtn_1_2 ||
            Button == ui->FusionTeamBtn_1_3 ||
            Button == ui->FusionTeamBtn_1_4 ||
            Button == ui->FusionTeamBtn_1_5 ||
            Button == ui->FusionTeamBtn_1_6 ||
            Button == ui->FusionTeamBtn_2_1 ||
            Button == ui->FusionTeamBtn_2_2 ||
            Button == ui->FusionTeamBtn_2_3 ||
            Button == ui->FusionTeamBtn_2_4 ||
            Button == ui->FusionTeamBtn_2_5 ||
            Button == ui->FusionTeamBtn_2_6 ||
            Button == ui->FusionTeamBtn_3_1 ||
            Button == ui->FusionTeamBtn_3_2 ||
            Button == ui->FusionTeamBtn_3_3 ||
            Button == ui->FusionTeamBtn_3_4 ||
            Button == ui->FusionTeamBtn_3_5 ||
            Button == ui->FusionTeamBtn_3_6 )
    {
        curBtn = 11;
    }


    if(curBtn == -1) return;

    int btnValue = gp->GetUByteParameter(Button);

    if(curBtn < 4)
    {
        rush[curBtn] = btnValue;
        Button->setText(rushStr[btnValue]);
    }
    else if(curBtn < 7)
    {
        curBtn -= 4;
        counter[curBtn] = btnValue;
        Button->setText(counterStr[btnValue]);
    }
    else if(curBtn < 10)
    {
        curBtn -= 7;
        fusion[curBtn] = btnValue;
        Button->setText(fusionStr[btnValue]);
    }
    else if(curBtn == 10)
    {
        Button->setText(charSelect.getItem(btnValue)->text());
        Button->setIcon(charSelect.getItem(btnValue)->icon());
    }
    else if(curBtn == 11)
    {
        Button->setIcon(charSelect.getItem(btnValue)->icon());
    }
}

void GeneralFrame::ResetUiMode()
{
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
    // Change the StyleSheet of Window + each Element
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));
    // Change the StyleSheet for the tooltips as well, can't leave them out now, can we?
    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(g_Options.GetStyledTooltip(lbl->toolTip()));
    }
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();
    for(QCheckBox* flag : flagBoxes)
    {
        if(flag->toolTip().isEmpty()) continue;
        flag->setToolTip(g_Options.GetStyledTooltip(flag->toolTip()));
    }
}
