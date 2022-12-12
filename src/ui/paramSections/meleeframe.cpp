#include "meleeframe.h"

MeleeFrame::MeleeFrame(PakControls* Pak, Options* options, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_MeleeFrame();
    ui->setupUi(this);

    this->options = options;

    mp = new MeleeParameters(Pak->GetParamData(MELEE), options);

    #if 1 // Passing the mp object the UI Elements
    mp->UiElements[MeleeParameters::Header] = ui->UnknownSpinBox_14;
    mp->UiElements[MeleeParameters::SecondaryString] = ui->SecStringFlag;
    mp->UiElements[MeleeParameters::LockOnLoss] = ui->LockOnLossFlag;
    mp->UiElements[MeleeParameters::Damage] = ui->DamageBox;
    mp->UiElements[MeleeParameters::DamageGuarding] = ui->DamageBox_2;
    mp->UiElements[MeleeParameters::KiGain] = ui->KiGainBox;
    mp->UiElements[MeleeParameters::KiLoss] = ui->KiLossBox;
    mp->UiElements[MeleeParameters::Unk14] = ui->UnknownSpinBox_1;
    mp->UiElements[MeleeParameters::Unk18] = ui->UnknownSpinBox_2;
    mp->UiElements[MeleeParameters::Unk1C] = ui->UnknownSpinBox_3;
    mp->UiElements[MeleeParameters::Hitstun] = ui->HitstunBox;
    mp->UiElements[MeleeParameters::Unk21] = ui->UnknownSpinBox_4;
    mp->UiElements[MeleeParameters::Unk22] = ui->UnknownSpinBox_5;
    mp->UiElements[MeleeParameters::Unk23] = ui->UnknownSpinBox_6;
    mp->UiElements[MeleeParameters::Unk24] = ui->UnknownSpinBox_7;
    mp->UiElements[MeleeParameters::Unk25] = ui->UnknownSpinBox_8;
    mp->UiElements[MeleeParameters::Unk26] = ui->UnknownSpinBox_9;
    mp->UiElements[MeleeParameters::Unk27] = ui->UnknownSpinBox_10;
    mp->UiElements[MeleeParameters::VFX] = ui->VFX_Box;
    mp->UiElements[MeleeParameters::SFX] = ui->SFX_Box;
    mp->UiElements[MeleeParameters::Unk2A] = ui->UnknownSpinBox_11;
    mp->UiElements[MeleeParameters::Unk2B] = ui->UnknownSpinBox_12;
    mp->UiElements[MeleeParameters::Knockback] = ui->KnockbackBox;
    mp->UiElements[MeleeParameters::Unk30] = ui->UnknownFloatBox_11;
    mp->UiElements[MeleeParameters::Reach] = ui->ReachBox;
    mp->UiElements[MeleeParameters::Unk38] = ui->UnknownFloatBox_1;
    mp->UiElements[MeleeParameters::Unk3C] = ui->UnknownFloatBox_2;
    mp->UiElements[MeleeParameters::Unk40] = ui->UnknownFloatBox_3;
    mp->UiElements[MeleeParameters::Unk44] = ui->UnknownFloatBox_4;
    mp->UiElements[MeleeParameters::Unk48] = ui->UnknownFloatBox_5;
    mp->UiElements[MeleeParameters::Unk4C] = ui->UnknownFloatBox_6;
    mp->UiElements[MeleeParameters::Unk50] = ui->UnknownFloatBox_7;
    mp->UiElements[MeleeParameters::Unk54] = ui->UnknownFloatBox_8;
    mp->UiElements[MeleeParameters::Unk58] = ui->UnknownFloatBox_9;
    mp->UiElements[MeleeParameters::Unk5C] = ui->UnknownFloatBox_10;
    mp->UiElements[MeleeParameters::EffectGuard] = ui->EOG_Box;
    mp->UiElements[MeleeParameters::EffectCounter] = ui->EOC_Box;
    mp->UiElements[MeleeParameters::GuardType] = ui->GuardBehaviourFlag;
    mp->UiElements[MeleeParameters::Unk63] = ui->UnknownSpinBox_13;
    #endif

    InitializeUIElements();
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
    if(ui->AttackSelectionBox->currentIndex() < 0)
    {

        for(QWidget* el : elements) el->setEnabled(false);
        for(QLabel* lbl : labels) lbl->setEnabled(true);
        ui->AttackSelectionBox->setEnabled(true);
        IsInitializing = false;
        return;
    }
    else for(QWidget* el : elements) el->setEnabled(true);

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
    if(options->GetUiMode() == Options::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");

        for(QSpinBox* spinBox : spinBoxes)
        {
            spinBox->setStyleSheet("");
        }
        for(QDoubleSpinBox* dblSpinBox : dblSpinBoxes)
        {
            dblSpinBox->setStyleSheet("");
        }
        for(QComboBox* comboBox : comboBoxes)
        {
            comboBox->setStyleSheet("");
        }
    }
    else if(options->GetUiMode() == Options::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");

        for(QSpinBox* spinBox : spinBoxes)
        {
            spinBox->setStyleSheet("background-color:rgb(65,69,75); color:white;border: 2 solid grey;");
        }
        for(QDoubleSpinBox* dblSpinBox : dblSpinBoxes)
        {
            dblSpinBox->setStyleSheet("background-color:rgb(65,69,75); color:white;border: 2 solid grey;");
        }
        for(QComboBox* comboBox : comboBoxes)
        {
            comboBox->setStyleSheet("background-color:rgb(65,69,75); color:white;border: 2 solid grey;");
        }
    }
    
    // Change the StyleSheet for the tooltips as well, can't leave them out now, can we?
    for(QLabel* lbl : labels)
    {
        if(lbl->toolTip().isEmpty()) continue;
        QString text = lbl->toolTip();
        text = text.split(">")[1];
        text.replace("</font>", "");
        lbl->setToolTip(options->GetStyledTooltip(lbl->toolTip()));
    }
    for(QCheckBox* flag : flagBoxes)
    {
        if(flag->toolTip().isEmpty()) continue;
        QString text = flag->toolTip();
        text = text.split(">")[1];
        text.replace("</font>", "");
        flagBoxes[i]->setToolTip(options->GetStyledTooltip(flag->toolTip()));
    }
}
