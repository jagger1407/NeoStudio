#include "generalframe.h"

GeneralFrame::GeneralFrame(PakControls* Pak, Options* options, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_GeneralFrame();
    ui->setupUi(this);

    this->options = options;

    gp = new GeneralParameters(Pak->GetParamData(GENERAL), options);

    #if 1 // Passing the gp Object all UI Elements
    gp->UiElements[GeneralParameters::Transform] = ui->TransformIDBox_1;
    gp->UiElements[GeneralParameters::Transform+1] = ui->TransformIDBox_2;
    gp->UiElements[GeneralParameters::Transform+2] = ui->TransformIDBox_3;
    gp->UiElements[GeneralParameters::Transform+3] = ui->TransformIDBox_4;
    gp->UiElements[GeneralParameters::TransformCost] = ui->TransformCostBox_1;
    gp->UiElements[GeneralParameters::TransformCost+1] = ui->TransformCostBox_2;
    gp->UiElements[GeneralParameters::TransformCost+2] = ui->TransformCostBox_3;
    gp->UiElements[GeneralParameters::TransformCost+3] = ui->TransformCostBox_4;
    gp->UiElements[GeneralParameters::FusionCost] = ui->FusionCostBox_1;
    gp->UiElements[GeneralParameters::FusionCost+1] = ui->FusionCostBox_2;
    gp->UiElements[GeneralParameters::FusionCost+2] = ui->FusionCostBox_3;
    gp->UiElements[GeneralParameters::FusionType] = ui->FusionTypeBtn_1;
    gp->UiElements[GeneralParameters::FusionType+1] = ui->FusionTypeBtn_2;
    gp->UiElements[GeneralParameters::FusionType+2] = ui->FusionTypeBtn_3;
    gp->UiElements[GeneralParameters::FusionCharID] = ui->FusionIDBox_1;
    gp->UiElements[GeneralParameters::FusionCharID+1] = ui->FusionIDBox_2;
    gp->UiElements[GeneralParameters::FusionCharID+2] = ui->FusionIDBox_3;
    gp->UiElements[GeneralParameters::FusionPartnerID] = ui->PartnerIDBox_1;
    gp->UiElements[GeneralParameters::FusionPartnerID+1] = ui->PartnerIDBox_2;
    gp->UiElements[GeneralParameters::FusionPartnerID+2] = ui->PartnerIDBox_3;
    gp->UiElements[GeneralParameters::FusionTeamID] = ui->PartnerTeamIDBox_1_1;
    gp->UiElements[GeneralParameters::FusionTeamID+1] = ui->PartnerTeamIDBox_1_2;
    gp->UiElements[GeneralParameters::FusionTeamID+2] = ui->PartnerTeamIDBox_1_3;
    gp->UiElements[GeneralParameters::FusionTeamID+3] = ui->PartnerTeamIDBox_1_4;
    gp->UiElements[GeneralParameters::FusionTeamID+4] = ui->PartnerTeamIDBox_1_5;
    gp->UiElements[GeneralParameters::FusionTeamID+5] = ui->PartnerTeamIDBox_1_6;
    gp->UiElements[GeneralParameters::FusionTeamID+6] = ui->PartnerTeamIDBox_2_1;
    gp->UiElements[GeneralParameters::FusionTeamID+7] = ui->PartnerTeamIDBox_2_2;
    gp->UiElements[GeneralParameters::FusionTeamID+8] = ui->PartnerTeamIDBox_2_3;
    gp->UiElements[GeneralParameters::FusionTeamID+9] = ui->PartnerTeamIDBox_2_4;
    gp->UiElements[GeneralParameters::FusionTeamID+10] = ui->PartnerTeamIDBox_2_5;
    gp->UiElements[GeneralParameters::FusionTeamID+11] = ui->PartnerTeamIDBox_2_6;
    gp->UiElements[GeneralParameters::FusionTeamID+12] = ui->PartnerTeamIDBox_3_1;
    gp->UiElements[GeneralParameters::FusionTeamID+13] = ui->PartnerTeamIDBox_3_2;
    gp->UiElements[GeneralParameters::FusionTeamID+14] = ui->PartnerTeamIDBox_3_3;
    gp->UiElements[GeneralParameters::FusionTeamID+15] = ui->PartnerTeamIDBox_3_4;
    gp->UiElements[GeneralParameters::FusionTeamID+16] = ui->PartnerTeamIDBox_3_5;
    gp->UiElements[GeneralParameters::FusionTeamID+17] = ui->PartnerTeamIDBox_3_6;
    gp->UiElements[GeneralParameters::ZSearch] = ui->ZSearchBox;
    gp->UiElements[GeneralParameters::FlagByte] = ui->FlagByteGroup_1;
    gp->UiElements[GeneralParameters::FlagByte+1] = ui->FlagByteGroup_2;
    gp->UiElements[GeneralParameters::FlagByte+2] = ui->FlagByteGroup_3;
    gp->UiElements[GeneralParameters::FlagByte+3] = ui->FlagByteGroup_4;
    gp->UiElements[GeneralParameters::FlagByte+4] = ui->FlagByteGroup_5;
    gp->UiElements[GeneralParameters::FlagByte+5] = ui->FlagByteGroup_6;
    gp->UiElements[GeneralParameters::FlagByte+6] = ui->FlagByteGroup_7;
    gp->UiElements[GeneralParameters::FlagByte+7] = ui->FlagByteGroup_8;
    gp->UiElements[GeneralParameters::FlagByte+8] = ui->FlagByteGroup_9;
    gp->UiElements[GeneralParameters::AuraColor] = ui->AuraColorBox;
    gp->UiElements[GeneralParameters::Collision] = ui->CollisionSpinBox_1;
    gp->UiElements[GeneralParameters::Collision+1] = ui->CollisionSpinBox_2;
    gp->UiElements[GeneralParameters::Collision+2] = ui->CollisionSpinBox_3;
    gp->UiElements[GeneralParameters::KiBlastAmount] = ui->KiBlastBox;
    gp->UiElements[GeneralParameters::RushingTechnique] = ui->RushTechBtn_1;
    gp->UiElements[GeneralParameters::RushingTechnique+1] = ui->RushTechBtn_2;
    gp->UiElements[GeneralParameters::RushingTechnique+2] = ui->RushTechBtn_3;
    gp->UiElements[GeneralParameters::RushingTechnique+3] = ui->RushTechBtn_4;
    gp->UiElements[GeneralParameters::CounterMove] = ui->CounterBtn_1;
    gp->UiElements[GeneralParameters::CounterMove+1] = ui->CounterBtn_2;
    gp->UiElements[GeneralParameters::CounterMove+2] = ui->CounterBtn_3;
    gp->UiElements[GeneralParameters::StepInMove] = ui->StepInBox;
    gp->UiElements[GeneralParameters::ChargedBlastAmount] = ui->KiBlastChargedBox;
    gp->UiElements[GeneralParameters::BlastStockAmount] = ui->BlastStockBox;
    gp->UiElements[GeneralParameters::KiChargeSpeed] = ui->KiChargeBox;
    gp->UiElements[GeneralParameters::KiChargeSpeedWater] = ui->KiChargeWaterBox;
    gp->UiElements[GeneralParameters::BaseKiRegen] = ui->BaseKiRegenBox;
    gp->UiElements[GeneralParameters::CounterKi] = ui->CounterKiBox;
    gp->UiElements[GeneralParameters::BlastGaugeSpeed] = ui->BlastGaugeBox;
    //gp->UiElements[GeneralParameters::MaxKiChargeSpeed] = ui->
    gp->UiElements[GeneralParameters::MaxPowerModeDuration] = ui->MaxPowDurBox;
    gp->UiElements[GeneralParameters::Gravity] = ui->GravityBox;
    gp->UiElements[GeneralParameters::MaxDragonSmashes] = ui->DragonHomingBox;
    gp->UiElements[GeneralParameters::MaxVanishingAttacks] = ui->VanishingAttackBox;
    gp->UiElements[GeneralParameters::MeleeChargeSpeed] = ui->ChargeBarSpdBox;
    gp->UiElements[GeneralParameters::DamageMultiplier] = ui->DmgMulBox;
    gp->UiElements[GeneralParameters::SwitchRegenSpeed] = ui->TeamGaugeBox;
    #endif

    if(Pak->HasFailed())
    {
        Debug::Log("GeneralFrame couldn't initialize pak file.", Debug::ERROR, options);
        return;
    }


    InitializeUIElements();
    ResetUiMode();
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
    else if(Button == ui->RushTechBtn_2)
            curBtn = 1;
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
        QString text = lbl->toolTip();
        text = text.split(">")[1];
        text.replace("</font>", "");
        lbl->setToolTip(options->GetStyledTooltip(lbl->toolTip()));
    }
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();
    for(QCheckBox* flag : flagBoxes)
    {
        if(flag->toolTip().isEmpty()) continue;
        QString text = flag->toolTip();
        text = text.split(">")[1];
        text.replace("</font>", "");
        flag->setToolTip(options->GetStyledTooltip(flag->toolTip()));
    }
}

