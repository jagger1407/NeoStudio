#include "meleeframe.h"

MeleeFrame::MeleeFrame(QByteArray Data, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_MeleeFrame();
    ui->setupUi(this);

    mp = new MeleeParameters(Data);

    #if 1 // Passing the pointers to the UI elements to mp
    mp->parameter[MeleeParameters::AttackFlags].UiElement = ui->AttackFlagGroup;
    mp->parameter[MeleeParameters::Damage].UiElement = ui->DamageBox;
    mp->parameter[MeleeParameters::DamageGuarding].UiElement = ui->DamageBox_2;
    mp->parameter[MeleeParameters::KiLoss].UiElement = ui->KiLossBox;
    mp->parameter[MeleeParameters::KiGain].UiElement = ui->KiGainBox;
    mp->parameter[MeleeParameters::Unk14].UiElement = ui->UnknownSpinBox_14;
    mp->parameter[MeleeParameters::Unk18].UiElement = ui->UnknownSpinBox_18;
    mp->parameter[MeleeParameters::Unk1C].UiElement = ui->UnknownSpinBox_1C;
    mp->parameter[MeleeParameters::Hitstun].UiElement = ui->HitstunBox;
    mp->parameter[MeleeParameters::Unk21].UiElement = ui->UnknownSpinBox_21;
    mp->parameter[MeleeParameters::Unk22].UiElement = ui->UnknownSpinBox_22;
    mp->parameter[MeleeParameters::Unk23].UiElement = ui->UnknownSpinBox_23;
    mp->parameter[MeleeParameters::Unk24].UiElement = ui->UnknownSpinBox_24;
    mp->parameter[MeleeParameters::Unk25].UiElement = ui->UnknownSpinBox_25;
    mp->parameter[MeleeParameters::Unk26].UiElement = ui->UnknownSpinBox_26;
    mp->parameter[MeleeParameters::Unk27].UiElement = ui->UnknownSpinBox_27;
    mp->parameter[MeleeParameters::VFX].UiElement = ui->VFX_Box;
    mp->parameter[MeleeParameters::SFX].UiElement = ui->SFX_Box;
    mp->parameter[MeleeParameters::Unk2A].UiElement = ui->UnknownSpinBox_2A;
    mp->parameter[MeleeParameters::Unk2B].UiElement = ui->UnknownSpinBox_2B;
    mp->parameter[MeleeParameters::Knockback].UiElement = ui->KnockbackBox;
    mp->parameter[MeleeParameters::Unk30].UiElement = ui->UnknownFloatBox_30;
    mp->parameter[MeleeParameters::Reach].UiElement = ui->ReachBox;
    mp->parameter[MeleeParameters::Unk38].UiElement = ui->UnknownFloatBox_38;
    mp->parameter[MeleeParameters::Unk3C].UiElement = ui->UnknownFloatBox_3C;
    mp->parameter[MeleeParameters::Unk40].UiElement = ui->UnknownFloatBox_40;
    mp->parameter[MeleeParameters::Unk44].UiElement = ui->UnknownFloatBox_44;
    mp->parameter[MeleeParameters::Unk48].UiElement = ui->UnknownFloatBox_48;
    mp->parameter[MeleeParameters::Unk4C].UiElement = ui->UnknownFloatBox_4C;
    mp->parameter[MeleeParameters::Unk50].UiElement = ui->UnknownFloatBox_50;
    mp->parameter[MeleeParameters::Unk54].UiElement = ui->UnknownFloatBox_54;
    mp->parameter[MeleeParameters::Unk58].UiElement = ui->UnknownFloatBox_58;
    mp->parameter[MeleeParameters::Unk5C].UiElement = ui->UnknownSpinBox_5C;
    mp->parameter[MeleeParameters::Unk5D].UiElement = ui->UnknownSpinBox_5D;
    mp->parameter[MeleeParameters::Unk5E].UiElement = ui->UnknownSpinBox_5E;
    mp->parameter[MeleeParameters::Unk5F].UiElement = ui->UnknownSpinBox_5F;
    mp->parameter[MeleeParameters::EffectGuard].UiElement = ui->EOG_Box;
    mp->parameter[MeleeParameters::EffectCounter].UiElement = ui->EOC_Box;
    mp->parameter[MeleeParameters::GuardType].UiElement = ui->GuardBehaviourFlag;
    mp->parameter[MeleeParameters::Unk63].UiElement = ui->UnknownSpinBox_63;
    #endif

    // The solution was so simple all this time...
    for(Param_Offset p : mp->parameter) ((QWidget*)p.UiElement)->setEnabled(false);

    IsInitializing = false;

    Debug::Log("MeleeFrame successfully constructed.", Debug::INFO);
}

void MeleeFrame::InitializeUIElements()
{
    IsInitializing = true;

    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(g_Options.GetStyledTooltip(lbl->toolTip()));
    }

    for(Param_Offset p : mp->parameter) ((QWidget*)p.UiElement)->setEnabled(true);

    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
    for(QSpinBox* sBox : spinBoxes)
    {
        if((unsigned int)sBox->maximum() < 256) sBox->setValue(mp->GetUByteParameter(sBox));
        else sBox->setValue(mp->GetIntParameter(sBox));
    }
    for(QDoubleSpinBox* dsBox : dblSpinBoxes)
    {
        dsBox->setValue(mp->GetFloatParameter(dsBox));
    }
    for(QCheckBox* flag : flagBoxes)
    {
        flag->setCheckState((Qt::CheckState)(mp->GetFlagParameter(flag) << 1));
    }
    for(QComboBox* cbBox : comboBoxes)
    {
        if(cbBox == ui->AttackSelectionBox) continue;
        cbBox->setCurrentIndex(mp->GetUByteParameter(cbBox));
    }

    IsInitializing = false;
}

void MeleeFrame::QSpinBox_Changed(int NewValue)
{
    if(IsInitializing || mp == nullptr) return;

    QSpinBox* box = (QSpinBox*)sender();
    if((unsigned int)box->maximum() < 256)
    {
        mp->SetUByteParameter(box, NewValue);
    }
    else
    {
        mp->SetIntParameter(box, NewValue);
    }
}
void MeleeFrame::QDoubleSpinBox_Changed(double NewValue)
{
    if(IsInitializing || mp == nullptr) return;

    QDoubleSpinBox* box = (QDoubleSpinBox*)sender();
    mp->SetFloatParameter(box, NewValue);
}
void MeleeFrame::CurrentAttack_IndexChanged(int NewIndex)
{
    if(IsInitializing || mp == nullptr) return;

    mp->setCurrentAttack(NewIndex);
    InitializeUIElements();
    Debug::Log(ui->AttackSelectionBox->currentText() + " (0x" + QString::number(NewIndex, 16) + ") Selected.", Debug::INFO);
}
void MeleeFrame::ComboBox_IndexChanged(int NewIndex)
{
    if(IsInitializing || mp == nullptr) return;

    QComboBox* box = (QComboBox*)sender();
    mp->SetUByteParameter(box, NewIndex);
}
void MeleeFrame::CheckBox_StateChanged(int NewState)
{
    if(IsInitializing || mp == nullptr) return;

    QCheckBox* flag = (QCheckBox*)sender();
    mp->SetFlagParameter(flag, NewState);
}

void MeleeFrame::ResetUiMode()
{
    // Getting all the UI Elements and categorizing them by type
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
    QList<QLabel*> labels = this->findChildren<QLabel*>();
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();

    // Change the StyleSheet of Window + each Element
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));
    // Change the StyleSheet for the tooltips as well, can't leave them out now, can we?
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(g_Options.GetStyledTooltip(lbl->toolTip()));
    }
    for(QCheckBox* flag : flagBoxes)
    {
        if(flag->toolTip().isEmpty()) continue;
        flag->setToolTip(g_Options.GetStyledTooltip(flag->toolTip()));
    }
}
