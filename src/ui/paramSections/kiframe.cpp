#include "kiframe.h"

KiFrame::KiFrame(QByteArray Data, Options* options, QWidget* parent) : QFrame(parent), options(options)
{
    ui = new Ui_KiFrame();
    ui->setupUi(this);

    kp = new KiParameters(Data, options);

    #if 1 // Passing the pointers to the UI elements to kp
    kp->parameter[KiParameters::Header].UiElement = ui->HeaderBox;
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

    QList<QWidget*> elements = this->findChildren<QWidget*>();
    QList<QLabel*> labels = this->findChildren<QLabel*>();
    for(QWidget* el : elements) el->setEnabled(false);
    for(QLabel* lbl : labels) lbl->setEnabled(true);
    ui->KiBlastSelectionBox->setEnabled(true);

    Debug::Log("New KiFrame constructed.", Debug::INFO, options);
}

void KiFrame::InitializeUIElements()
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
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
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

    IsInitializing = false;
}
void KiFrame::CurrentBlast_IndexChanged(int NewIndex)
{
    if(IsInitializing || kp == nullptr) return;
    Debug::Log("CurrentBlast_IndexChanged slot triggered.", Debug::INFO, options);
    kp->setCurrentBlast(NewIndex);
    InitializeUIElements();
}
void KiFrame::QSpinBox_Changed(int NewValue)
{
    if(IsInitializing || kp == nullptr) return;
    Debug::Log("QSpinBox_Changed slot triggered.", Debug::INFO, options);
    QSpinBox* object = (QSpinBox*)sender();
    if(object->maximum() > 255) kp->SetUByteParameter(object, NewValue);
    else kp->SetIntParameter(object, NewValue);

}
void KiFrame::QDoubleSpinBox_Changed(double NewValue)
{
    if(IsInitializing || kp == nullptr) return;
    Debug::Log("QDoubleSpinBox_Changed slot triggered.", Debug::INFO, options);
    kp->SetFloatParameter((QDoubleSpinBox*)sender(), NewValue);
}

void KiFrame::ComboBox_IndexChanged(int NewIndex)
{
    if(IsInitializing || kp == nullptr) return;
    Debug::Log("ComboBox_IndexChanged slot triggered.", Debug::INFO, options);
    kp->SetUByteParameter((QComboBox*)sender(), NewIndex);
}



void KiFrame::ResetUiMode()
{
    Debug::Log("ResetUiMode called.", Debug::INFO, options);

    // Getting all the UI Elements and categorizing them by type
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();
    QList<QLabel*> labels = this->findChildren<QLabel*>();

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
        lbl->setToolTip(options->GetStyledTooltip(lbl->toolTip()));
    }
}
