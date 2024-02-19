#include "kiframe.h"

KiFrame::KiFrame(QByteArray Data, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_KiFrame();
    ui->setupUi(this);

    kp = new KiParameters(Data);

    #if 1 // Passing the pointers to the UI elements to kp
    kp->parameter[KiParameters::Header].UiElement = ui->KiBlastFlagGroup;
    kp->parameter[KiParameters::Damage].UiElement = ui->DamageBox;
    kp->parameter[KiParameters::DamageGuarding].UiElement = ui->DamageGuardBox;
    kp->parameter[KiParameters::KiCost].UiElement = ui->KiCostBox;
    kp->parameter[KiParameters::Speed].UiElement = ui->SpeedBox;
    kp->parameter[KiParameters::Spread].UiElement = ui->SpreadBox;
    kp->parameter[KiParameters::Range].UiElement = ui->RangeBox;
    kp->parameter[KiParameters::Knockback].UiElement = ui->KnockbackBox;
    kp->parameter[KiParameters::Unk20].UiElement = ui->Unk20Box;
    kp->parameter[KiParameters::Hitstun].UiElement = ui->HitstunBox;
    kp->parameter[KiParameters::Unk25].UiElement = ui->Unk25Box;
    kp->parameter[KiParameters::Unk26].UiElement = ui->Unk26Box;
    kp->parameter[KiParameters::Unk27].UiElement = ui->Unk27Box;
    kp->parameter[KiParameters::Size].UiElement = ui->SizeBox;
    kp->parameter[KiParameters::Trail].UiElement = ui->TrailBox;
    kp->parameter[KiParameters::Unk30].UiElement = ui->Unk30Box;
    kp->parameter[KiParameters::Color].UiElement = ui->ColorBox;
    kp->parameter[KiParameters::Amount].UiElement = ui->AmountBox;
    kp->parameter[KiParameters::Trajectory].UiElement = ui->TrajectoryBox;
    kp->parameter[KiParameters::Footer].UiElement = ui->FooterBox;
    #endif

    // The solution was so simple all this time...
    for(Param_Offset p : kp->parameter) ((QWidget*)p.UiElement)->setEnabled(false);

    IsInitializing = false;

    Debug::Log("KiFrame successfully constructed.", Debug::INFO);
}

void KiFrame::InitializeUIElements()
{
    IsInitializing = true;

    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(g_Options.GetStyledTooltip(lbl->toolTip()));
    }

    for(Param_Offset p : kp->parameter) ((QWidget*)p.UiElement)->setEnabled(true);

    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();
    for(QSpinBox* sBox : spinBoxes)
    {
        if((unsigned int)sBox->maximum() < 256) sBox->setValue(kp->GetUByteParameter(sBox));
        else sBox->setValue(kp->GetIntParameter(sBox));
    }
    for(QDoubleSpinBox* dsBox : dblSpinBoxes)
    {
        dsBox->setValue(kp->GetFloatParameter(dsBox));
    }
    for(QComboBox* cbBox : comboBoxes)
    {
        if(cbBox == ui->KiBlastSelectionBox) continue;
        cbBox->setCurrentIndex(kp->GetUByteParameter(cbBox));
    }
    for(QCheckBox* flag : flagBoxes)
    {
        flag->setCheckState((Qt::CheckState)(kp->GetFlagParameter(flag) << 1));
    }

    IsInitializing = false;
}
void KiFrame::CurrentBlast_IndexChanged(int NewIndex)
{
    if(IsInitializing || kp == nullptr) return;

    kp->setCurrentBlast(NewIndex);
    InitializeUIElements();
    Debug::Log(ui->KiBlastSelectionBox->currentText() + " (0x" + QString::number(NewIndex, 16) + ") Selected.", Debug::INFO);
}
void KiFrame::QSpinBox_Changed(int NewValue)
{
    if(IsInitializing || kp == nullptr) return;

    QSpinBox* object = (QSpinBox*)sender();
    if(object->maximum() > 255) kp->SetUByteParameter(object, NewValue);
    else kp->SetIntParameter(object, NewValue);

}
void KiFrame::QDoubleSpinBox_Changed(double NewValue)
{
    if(IsInitializing || kp == nullptr) return;

    kp->SetFloatParameter((QDoubleSpinBox*)sender(), NewValue);
}

void KiFrame::ComboBox_IndexChanged(int NewIndex)
{
    if(IsInitializing || kp == nullptr) return;

    kp->SetUByteParameter((QComboBox*)sender(), NewIndex);
}
void KiFrame::CheckBox_StateChanged(int NewState)
{
    if(IsInitializing || kp == nullptr) return;

    QCheckBox* flag = (QCheckBox*)sender();
    kp->SetFlagParameter(flag, NewState);
}




void KiFrame::ResetUiMode()
{
    // Getting all the UI Elements and categorizing them by type
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
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
