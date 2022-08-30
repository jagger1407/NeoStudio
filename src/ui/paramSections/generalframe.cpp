#include "generalframe.h"

GeneralFrame::GeneralFrame(PakControls* Pak, QWidget* parent) : QFrame(parent)
{
    ui = new Ui_GeneralFrame();
    ui->setupUi(this);

    if(Pak->HasFailed())
    {
        Debug::Log("GeneralFrame couldn't initialize pak file.", Debug::ERROR);
        return;
    }
    gp = new GeneralParameters(Pak->GetParamData(GENERAL));

    InitializeUIElements();
}
void GeneralFrame::InitializeUIElements()
{
    Debug::Log("InitializeUIElements called.", Debug::INFO);
    IsInitializing = true;

    QList<QLabel*> labels = this->findChildren<QLabel*>();
    QList<QSpinBox*> spinBoxes = this->findChildren<QSpinBox*>();
    QList<QDoubleSpinBox*> dblSpinBoxes = this->findChildren<QDoubleSpinBox*>();
    QList<QCheckBox*> flagBoxes = this->findChildren<QCheckBox*>();
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    QList<QComboBox*> comboBoxes = this->findChildren<QComboBox*>();

    for(int i=0;i<labels.count();i++)
    {
        if(!labels[i]->toolTip().isEmpty()) labels[i]->setToolTip("<font color=\"black\">" + labels[i]->toolTip() + "</font>");
    }
    for(int i=0;i<spinBoxes.count();i++)
    {
        if(spinBoxes[i]->maximum() > 255) spinBoxes[i]->setValue(gp->GetIntParameter(spinBoxes[i]->objectName()));
        else spinBoxes[i]->setValue(gp->GetUByteParameter(spinBoxes[i]->objectName()));
        Debug::ConsolePrint(QString::number(spinBoxes[i]->value()), Debug::INFO);
    }
    for(int i=0;i<dblSpinBoxes.count();i++)
    {
        dblSpinBoxes[i]->setValue(gp->GetFloatParameter(dblSpinBoxes[i]->objectName()));
    }
    for(int i=0;i<flagBoxes.count();i++)
    {
        if(!flagBoxes[i]->toolTip().isEmpty()) flagBoxes[i]->setToolTip("<font color=\"black\">" + flagBoxes[i]->toolTip() + "</font>");
        flagBoxes[i]->setCheckState((Qt::CheckState)(gp->GetFlagParameter(flagBoxes[i]->objectName())*2));
    }
    for(int i=0;i<buttons.count();i++)
    {
        ButtonValueGet(buttons[i]);
    }
    for(int i=0;i<comboBoxes.count();i++)
    {
        comboBoxes[i]->setCurrentIndex(gp->GetUByteParameter(comboBoxes[i]->objectName()));
    }

    IsInitializing = false;
}
void GeneralFrame::QSpinBox_Changed(int NewValue)
{
    if(IsInitializing) return;
    Debug::Log("QSpinBox_Changed slot triggered.", Debug::INFO);
    QSpinBox* spinBox = (QSpinBox*)sender();
    if(spinBox->maximum() > 255) gp->SetIntParameter(spinBox->objectName(), NewValue);
    else gp->SetUByteParameter(spinBox->objectName(), NewValue);
}
void GeneralFrame::QDoubleSpinBox_Changed(double NewValue)
{
    if(IsInitializing) return;
    Debug::Log("QDoubleSpinBox_Changed slot triggered.", Debug::INFO);
    QDoubleSpinBox* dblSpinBox = (QDoubleSpinBox*)sender();
    gp->SetFloatParameter(dblSpinBox->objectName(), (float)NewValue);
}
void GeneralFrame::Button_Clicked()
{
    if(IsInitializing) return;
    Debug::Log("Button_Clicked slot triggered.", Debug::INFO);
    QPushButton* button = (QPushButton*)sender();
    ButtonChange(button);
}
void GeneralFrame::ComboBox_IndexChanged(int NewValue)
{
    if(IsInitializing) return;
    Debug::Log("ComboBox_IndexChanged slot triggered.", Debug::INFO);
    gp->SetUByteParameter(sender()->objectName(), NewValue);
}
void GeneralFrame::Flag_Changed(int NewValue)
{
    if(IsInitializing) return;
    Debug::Log("Flag_Changed slot triggered.", Debug::INFO);
    gp->SetFlagParameter(sender()->objectName(), NewValue);
}
void GeneralFrame::ButtonChange(QPushButton* Button)
{
    if(Button->objectName().contains("RushTech"))
    {
        if(Button->text() == "None")
        {
            gp->SetUByteParameter(Button->objectName(), HEAVY);
            Button->setText("Heavy Finish");
        }
        else if(Button->text() == "Heavy Finish")
        {
            gp->SetUByteParameter(Button->objectName(), KIAI);
            Button->setText("Kiai Cannon");
        }
        else if(Button->text() == "Kiai Cannon")
        {
            gp->SetUByteParameter(Button->objectName(), FLYING_KICKS);
            Button->setText("Flying Kicks");
        }
        else if(Button->text() == "Flying Kicks")
        {
            gp->SetUByteParameter(Button->objectName(), NO_TECHNIQUE);
            Button->setText("None");
        }
    }
    else if(Button->objectName().contains("Counter"))
    {
        if(Button->text() == "No Counter")
        {
            gp->SetUByteParameter(Button->objectName(), SMASH);
            Button->setText("Smash");
        }
        else if(Button->text() == "Smash")
        {
            gp->SetUByteParameter(Button->objectName(), FEINT);
            Button->setText("Vanish");
        }
        else if(Button->text() == "Vanish")
        {
            gp->SetUByteParameter(Button->objectName(), THROW);
            Button->setText("Throw");
        }
        else if(Button->text() == "Throw")
        {
            gp->SetUByteParameter(Button->objectName(), SWAY);
            Button->setText("Sway");
        }
        else if(Button->text() == "Sway")
        {
            gp->SetUByteParameter(Button->objectName(), NO_COUNTER);
            Button->setText("No Counter");
        }
    }
}
void GeneralFrame::ButtonValueGet(QPushButton* Button)
{
    if(Button->objectName().contains("RushTech"))
    {
        switch(gp->GetUByteParameter(Button->objectName()))
        {
            case NO_TECHNIQUE:
                Button->setText("None");
                break;
            case HEAVY:
                Button->setText("Heavy Finish");
                break;
            case KIAI:
                Button->setText("Kiai Cannon");
                break;
            case FLYING_KICKS:
                Button->setText("Flying Kicks");
                break;
            default:
                Button->setText("Unknown");
        }
    }
    else if(Button->objectName().contains("Counter"))
    {
        switch(gp->GetUByteParameter(Button->objectName()))
        {
            case NO_COUNTER:
                Button->setText("No Counter");
                break;
            case SMASH:
                Button->setText("Smash");
                break;
            case FEINT:
                Button->setText("Vanish");
                break;
            case THROW:
                Button->setText("Throw");
                break;
            case SWAY:
                Button->setText("Sway");
                break;
            default:
                Button->setText("Unkown");
        }
    }
}
