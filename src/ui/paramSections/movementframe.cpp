#include "movementframe.h"
#include "ui_movementframe.h"

MovementFrame::MovementFrame(QByteArray Data, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_MovementFrame();
    ui->setupUi(this);

    mp = new MovementParameters(Data);

    #if 1 // Passing the pointers to the UI elements to kp
    mp->parameter[MovementParameters::RegMovSpeed].UiElement = ui->MovSpeedBox;
    mp->parameter[MovementParameters::RegMovSpeedWater].UiElement = ui->MovSpeedWaterBox;
        mp->parameter[MovementParameters::CRMoveSpeed].UiElement = ui->CRMovSpeedBox;
        mp->parameter[MovementParameters::CRMoveSpeedWater].UiElement = ui->CRMovSpeedWaterBox;
        mp->parameter[MovementParameters::DashSpeed].UiElement = ui->DashSpeedBox;
        mp->parameter[MovementParameters::DashSpeedWater].UiElement = ui->WDashSpeedBox;
        mp->parameter[MovementParameters::DDC_Speed].UiElement = ui->DDCSpeedBox;
        mp->parameter[MovementParameters::DDF_Speed].UiElement = ui->DDFSpeedBox;
        mp->parameter[MovementParameters::DDRF_Speed].UiElement = ui->DDRFSpeedBox;
        mp->parameter[MovementParameters::DAscDesc_Speed].UiElement = ui->DADDSpeedBox;
        mp->parameter[MovementParameters::StepInSpeed].UiElement = ui->StepInBox;
        mp->parameter[MovementParameters::BackstepSpeed].UiElement = ui->BackstepBox;
        mp->parameter[MovementParameters::SidestepSpeed].UiElement = ui->SidestepBox;
        mp->parameter[MovementParameters::JumpSpeed].UiElement = ui->JumpSpeedBox;
        mp->parameter[MovementParameters::DashJumpSpeed].UiElement = ui->DJumpSpeedBox;
        mp->parameter[MovementParameters::LiftStrikeJumpSpeed].UiElement = ui->LiftStrikeBox;
        mp->parameter[MovementParameters::AscSpeed].UiElement = ui->AscSpeedBox;
        mp->parameter[MovementParameters::DescSpeed].UiElement = ui->DescSpeedBox;
        mp->parameter[MovementParameters::TeleportSpeed].UiElement = ui->RMHSMSpeedBox;
        mp->parameter[MovementParameters::AscAcceleration].UiElement = ui->AscAccelBox;
        mp->parameter[MovementParameters::DescAcceleration].UiElement = ui->DescAccelBox;
        mp->parameter[MovementParameters::Unk54].UiElement = ui->Unk54Box;
        mp->parameter[MovementParameters::DashLength].UiElement = ui->DashLengthBox;
        mp->parameter[MovementParameters::Unk5C].UiElement = ui->Unk5CBox;
        mp->parameter[MovementParameters::Unk60].UiElement = ui->Unk60Box;
        mp->parameter[MovementParameters::Unk64].UiElement = ui->Unk64Box;
        mp->parameter[MovementParameters::JumpHeight].UiElement = ui->JumpHeightBox;
        mp->parameter[MovementParameters::DashJumpHeight].UiElement = ui->DJumpHeightBox;
        mp->parameter[MovementParameters::DDC_Consumption].UiElement = ui->DDCKiConBox;
        mp->parameter[MovementParameters::DDF_Consumption].UiElement = ui->DDFKiConBox;
        mp->parameter[MovementParameters::DAscDDesc_Consumption].UiElement = ui->DADDKiConBox;
        mp->parameter[MovementParameters::Unk7C].UiElement = ui->Unk7CBox;
        mp->parameter[MovementParameters::HDDTSC].UiElement = ui->HDDTS_Box;
        mp->parameter[MovementParameters::Unk84].UiElement = ui->Unk84Box;
        mp->parameter[MovementParameters::Unk88].UiElement = ui->Unk88Box;
        mp->parameter[MovementParameters::Unk8C].UiElement = ui->Unk8CBox;
        mp->parameter[MovementParameters::Unk90].UiElement = ui->Unk90Box;
        mp->parameter[MovementParameters::Unk94].UiElement = ui->Unk94Box;
        mp->parameter[MovementParameters::VDDTSC].UiElement = ui->VDDTS_Box;
        mp->parameter[MovementParameters::Unk9C].UiElement = ui->Unk9CBox;
        mp->parameter[MovementParameters::UnkA0].UiElement = ui->UnkA0Box;
    #endif

    InitializeUIElements();
    ResetUiMode();
    Debug::Log("New MovementFrame constructed.", Debug::INFO);
}

void MovementFrame::InitializeUIElements()
{
    Debug::Log("InitializeUIElements called.", Debug::INFO);

    IsInitializing = true;

    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(g_Options.GetStyledTooltip(lbl->toolTip()));
    }

    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    for(QSpinBox* sBox : spinBoxes)
    {
        sBox->setValue(mp->GetIntParameter(sBox));
    }
    for(QDoubleSpinBox* dsBox : dblSpinBoxes)
    {
        dsBox->setValue(mp->GetFloatParameter(dsBox));
    }

    IsInitializing = false;
}

void MovementFrame::QSpinBox_Changed(int NewValue)
{
    Debug::Log("QSpinBox_Changed slot triggered.", Debug::INFO);
    QSpinBox* box = (QSpinBox*)sender();
    mp->SetIntParameter(box, NewValue);
}
void MovementFrame::QDoubleSpinBox_Changed(double NewValue)
{
    Debug::Log("QDoubleSpinBox_Changed slot triggered.", Debug::INFO);
    QDoubleSpinBox* box = (QDoubleSpinBox*)sender();
    mp->SetFloatParameter(box, NewValue);
}

void MovementFrame::ResetUiMode()
{
    Debug::Log("ResetUiMode called.", Debug::INFO);

    // Getting all the UI Elements and categorizing them by type
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QLabel*> labels = this->findChildren<QLabel*>();

    // Change the StyleSheet of Window + each Element
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));
    // Change the StyleSheet for the tooltips as well, can't leave them out now, can we?
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(g_Options.GetStyledTooltip(lbl->toolTip()));
    }
}
