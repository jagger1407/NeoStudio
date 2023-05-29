#include "meleeframe.h"

MeleeFrame::MeleeFrame(QByteArray Data, Options* options, QWidget* parent) : QFrame(parent), options(options)
{
    ui = new Ui_MeleeFrame();
    ui->setupUi(this);

    mp = new MeleeParameters(Data, options);

    #if 1 // Passing the pointers to the UI elements to mp
    mp->parameter[MeleeParameters::Header].UiElement = ui->UnknownSpinBox_14;
    mp->parameter[MeleeParameters::SecondaryString].UiElement = ui->SecStringFlag;
    mp->parameter[MeleeParameters::LockOnLoss].UiElement = ui->LockOnLossFlag;
    mp->parameter[MeleeParameters::Damage].UiElement = ui->DamageBox;
    mp->parameter[MeleeParameters::DamageGuarding].UiElement = ui->DamageBox_2;
    mp->parameter[MeleeParameters::KiGain].UiElement = ui->KiGainBox;
    mp->parameter[MeleeParameters::KiLoss].UiElement = ui->KiLossBox;
    mp->parameter[MeleeParameters::Unk14].UiElement = ui->UnknownSpinBox_1;
    mp->parameter[MeleeParameters::Unk18].UiElement = ui->UnknownSpinBox_2;
    mp->parameter[MeleeParameters::Unk1C].UiElement = ui->UnknownSpinBox_3;
    mp->parameter[MeleeParameters::Hitstun].UiElement = ui->HitstunBox;
    mp->parameter[MeleeParameters::Unk21].UiElement = ui->UnknownSpinBox_4;
    mp->parameter[MeleeParameters::Unk22].UiElement = ui->UnknownSpinBox_5;
    mp->parameter[MeleeParameters::Unk23].UiElement = ui->UnknownSpinBox_6;
    mp->parameter[MeleeParameters::Unk24].UiElement = ui->UnknownSpinBox_7;
    mp->parameter[MeleeParameters::Unk25].UiElement = ui->UnknownSpinBox_8;
    mp->parameter[MeleeParameters::Unk26].UiElement = ui->UnknownSpinBox_9;
    mp->parameter[MeleeParameters::Unk27].UiElement = ui->UnknownSpinBox_10;
    mp->parameter[MeleeParameters::VFX].UiElement = ui->VFX_Box;
    mp->parameter[MeleeParameters::SFX].UiElement = ui->SFX_Box;
    mp->parameter[MeleeParameters::Unk2A].UiElement = ui->UnknownSpinBox_11;
    mp->parameter[MeleeParameters::Unk2B].UiElement = ui->UnknownSpinBox_12;
    mp->parameter[MeleeParameters::Knockback].UiElement = ui->KnockbackBox;
    mp->parameter[MeleeParameters::Unk30].UiElement = ui->UnknownFloatBox_11;
    mp->parameter[MeleeParameters::Reach].UiElement = ui->ReachBox;
    mp->parameter[MeleeParameters::Unk38].UiElement = ui->UnknownFloatBox_1;
    mp->parameter[MeleeParameters::Unk3C].UiElement = ui->UnknownFloatBox_2;
    mp->parameter[MeleeParameters::Unk40].UiElement = ui->UnknownFloatBox_3;
    mp->parameter[MeleeParameters::Unk44].UiElement = ui->UnknownFloatBox_4;
    mp->parameter[MeleeParameters::Unk48].UiElement = ui->UnknownFloatBox_5;
    mp->parameter[MeleeParameters::Unk4C].UiElement = ui->UnknownFloatBox_6;
    mp->parameter[MeleeParameters::Unk50].UiElement = ui->UnknownFloatBox_7;
    mp->parameter[MeleeParameters::Unk54].UiElement = ui->UnknownFloatBox_8;
    mp->parameter[MeleeParameters::Unk58].UiElement = ui->UnknownFloatBox_9;
    mp->parameter[MeleeParameters::Unk5C].UiElement = ui->UnknownFloatBox_10;
    mp->parameter[MeleeParameters::EffectGuard].UiElement = ui->EOG_Box;
    mp->parameter[MeleeParameters::EffectCounter].UiElement = ui->EOC_Box;
    mp->parameter[MeleeParameters::GuardType].UiElement = ui->GuardBehaviourFlag;
    mp->parameter[MeleeParameters::Unk63].UiElement = ui->UnknownSpinBox_13;
    #endif

    QList<QWidget*> elements = this->findChildren<QWidget*>();
    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QWidget* el : elements) el->setEnabled(false);
    for(QLabel* lbl : labels) lbl->setEnabled(true);
    ui->AttackSelectionBox->setEnabled(true);

    Debug::Log("New MeleeFrame constructed.", Debug::INFO, options);
}

void MeleeFrame::InitializeUIElements()
{
    Debug::Log("InitializeUIElements called.", Debug::INFO, options);

    IsInitializing = true;

    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(options->GetStyledTooltip(lbl->toolTip()));
    }

    QList<QWidget*> elements = this->findChildren<QWidget*>();
    for(QWidget* el : elements) el->setEnabled(true);

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
    Debug::Log("QSpinBox_Changed slot triggered.", Debug::INFO, options);
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
    Debug::Log("QDoubleSpinBox_Changed slot triggered.", Debug::INFO, options);
    QDoubleSpinBox* box = (QDoubleSpinBox*)sender();
    mp->SetFloatParameter(box, NewValue);
}
void MeleeFrame::CurrentAttack_IndexChanged(int NewIndex)
{
    if(mp == nullptr) return;
    Debug::Log("CurrentAttack_IndexChanged slot triggered.", Debug::INFO, options);
    mp->setCurrentAttack(NewIndex);
    InitializeUIElements();
}
void MeleeFrame::ComboBox_IndexChanged(int NewIndex)
{
    if(IsInitializing || mp == nullptr) return;
    Debug::Log("ComboBox_IndexChanged slot triggered.", Debug::INFO, options);
    QComboBox* box = (QComboBox*)sender();
    mp->SetUByteParameter(box, NewIndex);
}
void MeleeFrame::CheckBox_StateChanged(int NewState)
{
    if(IsInitializing || mp == nullptr) return;
    Debug::Log("CheckBox_StateChanged slot triggered.", Debug::INFO, options);
    QCheckBox* flag = (QCheckBox*)sender();
    mp->SetFlagParameter(flag, NewState);
}

void MeleeFrame::ResetUiMode()
{
    Debug::Log("ResetUiMode called.", Debug::INFO, options);

    // Getting all the UI Elements and categorizing them by type
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
    QList<QLabel*> labels = this->findChildren<QLabel*>();
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();

    // Change the StyleSheet of Window + each Element
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + options->GetUiMode() + ".qss"));
    // Change the StyleSheet for the tooltips as well, can't leave them out now, can we?
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        lbl->setToolTip(options->GetStyledTooltip(lbl->toolTip()));
    }
    for(QCheckBox* flag : flagBoxes)
    {
        if(flag->toolTip().isEmpty()) continue;
        flag->setToolTip(options->GetStyledTooltip(flag->toolTip()));
    }
}
