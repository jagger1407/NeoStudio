#include "generalframe.h"

GeneralFrame::GeneralFrame(QByteArray Data, Options* options, QWidget* parent) : QFrame(parent), options(options)
{
    ui = new Ui_GeneralFrame();
    ui->setupUi(this);

    gp = new GeneralParameters(Data, options);

    #if 1 // Passing the gp Object all UI Elements
    gp->parameter[GeneralParameters::Transform].UiElement = ui->TransformIDBox_1;
    gp->parameter[GeneralParameters::Transform+1].UiElement = ui->TransformIDBox_2;
    gp->parameter[GeneralParameters::Transform+2].UiElement = ui->TransformIDBox_3;
    gp->parameter[GeneralParameters::Transform+3].UiElement = ui->TransformIDBox_4;
    gp->parameter[GeneralParameters::TransformCost].UiElement = ui->TransformCostBox_1;
    gp->parameter[GeneralParameters::TransformCost+1].UiElement = ui->TransformCostBox_2;
    gp->parameter[GeneralParameters::TransformCost+2].UiElement = ui->TransformCostBox_3;
    gp->parameter[GeneralParameters::TransformCost+3].UiElement = ui->TransformCostBox_4;
    gp->parameter[GeneralParameters::FusionCost].UiElement = ui->FusionCostBox_1;
    gp->parameter[GeneralParameters::FusionCost+1].UiElement = ui->FusionCostBox_2;
    gp->parameter[GeneralParameters::FusionCost+2].UiElement = ui->FusionCostBox_3;
    gp->parameter[GeneralParameters::FusionType].UiElement = ui->FusionTypeBtn_1;
    gp->parameter[GeneralParameters::FusionType+1].UiElement = ui->FusionTypeBtn_2;
    gp->parameter[GeneralParameters::FusionType+2].UiElement = ui->FusionTypeBtn_3;
    gp->parameter[GeneralParameters::FusionCharID].UiElement = ui->FusionIDBox_1;
    gp->parameter[GeneralParameters::FusionCharID+1].UiElement = ui->FusionIDBox_2;
    gp->parameter[GeneralParameters::FusionCharID+2].UiElement = ui->FusionIDBox_3;
    gp->parameter[GeneralParameters::FusionPartnerID].UiElement = ui->PartnerIDBox_1;
    gp->parameter[GeneralParameters::FusionPartnerID+1].UiElement = ui->PartnerIDBox_2;
    gp->parameter[GeneralParameters::FusionPartnerID+2].UiElement = ui->PartnerIDBox_3;
    gp->parameter[GeneralParameters::FusionTeamID].UiElement = ui->PartnerTeamIDBox_1_1;
    gp->parameter[GeneralParameters::FusionTeamID+1].UiElement = ui->PartnerTeamIDBox_1_2;
    gp->parameter[GeneralParameters::FusionTeamID+2].UiElement = ui->PartnerTeamIDBox_1_3;
    gp->parameter[GeneralParameters::FusionTeamID+3].UiElement = ui->PartnerTeamIDBox_1_4;
    gp->parameter[GeneralParameters::FusionTeamID+4].UiElement = ui->PartnerTeamIDBox_1_5;
    gp->parameter[GeneralParameters::FusionTeamID+5].UiElement = ui->PartnerTeamIDBox_1_6;
    gp->parameter[GeneralParameters::FusionTeamID+6].UiElement = ui->PartnerTeamIDBox_2_1;
    gp->parameter[GeneralParameters::FusionTeamID+7].UiElement = ui->PartnerTeamIDBox_2_2;
    gp->parameter[GeneralParameters::FusionTeamID+8].UiElement = ui->PartnerTeamIDBox_2_3;
    gp->parameter[GeneralParameters::FusionTeamID+9].UiElement = ui->PartnerTeamIDBox_2_4;
    gp->parameter[GeneralParameters::FusionTeamID+10].UiElement = ui->PartnerTeamIDBox_2_5;
    gp->parameter[GeneralParameters::FusionTeamID+11].UiElement = ui->PartnerTeamIDBox_2_6;
    gp->parameter[GeneralParameters::FusionTeamID+12].UiElement = ui->PartnerTeamIDBox_3_1;
    gp->parameter[GeneralParameters::FusionTeamID+13].UiElement = ui->PartnerTeamIDBox_3_2;
    gp->parameter[GeneralParameters::FusionTeamID+14].UiElement = ui->PartnerTeamIDBox_3_3;
    gp->parameter[GeneralParameters::FusionTeamID+15].UiElement = ui->PartnerTeamIDBox_3_4;
    gp->parameter[GeneralParameters::FusionTeamID+16].UiElement = ui->PartnerTeamIDBox_3_5;
    gp->parameter[GeneralParameters::FusionTeamID+17].UiElement = ui->PartnerTeamIDBox_3_6;
    gp->parameter[GeneralParameters::ZSearch].UiElement = ui->ZSearchBox;
    gp->parameter[GeneralParameters::FlagByte].UiElement = ui->FlagByteGroup_1;
    gp->parameter[GeneralParameters::FlagByte+1].UiElement = ui->FlagByteGroup_2;
    gp->parameter[GeneralParameters::FlagByte+2].UiElement = ui->FlagByteGroup_3;
    gp->parameter[GeneralParameters::FlagByte+3].UiElement = ui->FlagByteGroup_4;
    gp->parameter[GeneralParameters::FlagByte+4].UiElement = ui->FlagByteGroup_5;
    gp->parameter[GeneralParameters::FlagByte+5].UiElement = ui->FlagByteGroup_6;
    gp->parameter[GeneralParameters::FlagByte+6].UiElement = ui->FlagByteGroup_7;
    gp->parameter[GeneralParameters::FlagByte+7].UiElement = ui->FlagByteGroup_8;
    gp->parameter[GeneralParameters::FlagByte+8].UiElement = ui->FlagByteGroup_9;
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
    gp->parameter[GeneralParameters::ChargedBlastAmount].UiElement = ui->KiBlastChargedBox;
    gp->parameter[GeneralParameters::BlastStockAmount].UiElement = ui->BlastStockBox;
    gp->parameter[GeneralParameters::KiChargeSpeed].UiElement = ui->KiChargeBox;
    gp->parameter[GeneralParameters::KiChargeSpeedWater].UiElement = ui->KiChargeWaterBox;
    gp->parameter[GeneralParameters::BaseKiRegen].UiElement = ui->BaseKiRegenBox;
    gp->parameter[GeneralParameters::CounterKi].UiElement = ui->CounterKiBox;
    gp->parameter[GeneralParameters::BlastGaugeSpeed].UiElement = ui->BlastGaugeBox;
    gp->parameter[GeneralParameters::BlueKiChargeSpeed].UiElement = ui->BlueKiChargeBox;
    gp->parameter[GeneralParameters::MaxPowerModeDuration].UiElement = ui->MaxPowDurBox;
    gp->parameter[GeneralParameters::Gravity].UiElement = ui->GravityBox;
    gp->parameter[GeneralParameters::MaxDragonSmashes].UiElement = ui->DragonHomingBox;
    gp->parameter[GeneralParameters::MaxVanishingAttacks].UiElement = ui->VanishingAttackBox;
    gp->parameter[GeneralParameters::MeleeChargeSpeed].UiElement = ui->ChargeBarSpdBox;
    gp->parameter[GeneralParameters::DamageMultiplier].UiElement = ui->DmgMulBox;
    gp->parameter[GeneralParameters::SwitchRegenSpeed].UiElement = ui->TeamGaugeBox;
    #endif

    InitializeUIElements();
    ResetUiMode();
    Debug::Log("New GeneralFrame constructed.", Debug::INFO, options);
}
void GeneralFrame::InitializeUIElements()
{
    Debug::Log("InitializeUIElements called.", Debug::INFO, options);
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
        lbl->setToolTip(options->GetStyledTooltip(lbl->toolTip()));
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
        if(!flag->toolTip().isEmpty()) flag->setToolTip(options->GetStyledTooltip(flag->toolTip()));
        flag->setCheckState((Qt::CheckState)(gp->GetFlagParameter(flag) << 1));
    }
    for(QPushButton* btn : buttons)
    {
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
    Debug::Log("QSpinBox_Changed slot triggered.", Debug::INFO, options);
    QSpinBox* spinBox = (QSpinBox*)sender();
    if(spinBox->maximum() > 255) gp->SetIntParameter(spinBox, NewValue);
    else
    {
        if(spinBox->objectName().contains("ID"))
        {
            if(NewValue > ROSTER_SIZE)
            {
                gp->SetUByteParameter(spinBox, 255);
                spinBox->setValue(255);
            }
            else gp->SetUByteParameter(spinBox, NewValue);
        }
    }
}
void GeneralFrame::QDoubleSpinBox_Changed(double NewValue)
{
    if(IsInitializing || gp == nullptr) return;
    Debug::Log("QDoubleSpinBox_Changed slot triggered.", Debug::INFO, options);
    QDoubleSpinBox* dblSpinBox = (QDoubleSpinBox*)sender();
    gp->SetFloatParameter(dblSpinBox, (float)NewValue);
}
void GeneralFrame::Button_Clicked()
{
    if(IsInitializing || gp == nullptr) return;
    Debug::Log("Button_Clicked slot triggered.", Debug::INFO, options);
    QPushButton* button = (QPushButton*)sender();
    ButtonChange(button);
}
void GeneralFrame::ComboBox_IndexChanged(int NewValue)
{
    if(IsInitializing || gp == nullptr) return;
    Debug::Log("ComboBox_IndexChanged slot triggered.", Debug::INFO, options);
    gp->SetUByteParameter((QComboBox*)sender(), NewValue);
}
void GeneralFrame::Flag_Changed(int NewValue)
{
    if(IsInitializing || gp == nullptr) return;
    Debug::Log("Flag_Changed slot triggered.", Debug::INFO, options);
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
        else
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
    else
    {
        curBtn -= 7;
        counter[curBtn] = btnValue;
        Button->setText(fusionStr[btnValue]);
    }
}

void GeneralFrame::ResetUiMode()
{
    Debug::Log("ResetUiMode called.", Debug::INFO, options);

    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
    if(options->GetUiMode() == Options::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");

        for(QSpinBox* sBox : spinBoxes)
        {
            sBox->setStyleSheet("");
        }
        for(QDoubleSpinBox* dsBox : dblSpinBoxes)
        {
            dsBox->setStyleSheet("");
        }
        for(QComboBox* cbBox : comboBoxes)
        {
            cbBox->setStyleSheet("");
        }
    }
    else if(options->GetUiMode() == Options::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");

        for(QSpinBox* sBox : spinBoxes)
        {
            sBox->setStyleSheet("background-color:rgb(65,69,75); color:white;border: 2 solid grey;");
        }
        for(QDoubleSpinBox* dsBox : dblSpinBoxes)
        {
            dsBox->setStyleSheet("background-color:rgb(65,69,75); color:white;border: 2 solid grey;");
        }
        for(QComboBox* cbBox : comboBoxes)
        {
            cbBox->setStyleSheet("background-color:rgb(65,69,75); color:white;border: 2 solid grey;");
        }
    }
    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(options->GetStyledTooltip(lbl->toolTip()));
    }
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();
    for(QCheckBox* flag : flagBoxes)
    {
        if(flag->toolTip().isEmpty()) continue;
        flag->setToolTip(options->GetStyledTooltip(flag->toolTip()));
    }
}
