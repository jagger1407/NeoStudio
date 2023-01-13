#include "optiondialog.h"

OptionDialog::OptionDialog(Options* options)
    : ui(new Ui::OptionDialog), options(options)
{
    int logMode = this->options->GetLogMode();
    int uiMode = this->options->GetUiMode();
    int tool = this->options->GetTooltipColor();
    bool advanced = this->options->GetAdvancedOptions();
    if(uiMode == Options::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");
    }
    else if(uiMode == Options::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");
    }
    ui->setupUi(this);
    this->setWindowTitle("Options");
    this->setWindowIcon(QIcon("./assets/cog-wheel.png"));

    ui->LogModeBox->setCurrentIndex(logMode);
    ui->TooltipBox->setCurrentIndex(tool);
    ui->UiModeBox->setCurrentIndex((int)uiMode);
    ui->DebugEnableCheckBox->setCheckState((Qt::CheckState)(advanced << 1));

    if(!advanced)
    {
        ui->LogModeBox->setStyleSheet("color:grey");
        ui->LogModeLbl->setStyleSheet("color:grey");
    }


    Debug::Log("OptionDialog constructed.", Debug::INFO, this->options);
}

void OptionDialog::DebugEnableCheckState_Changed(int NewState)
{
    Debug::Log("DebugEnableCheckState_Changed slot triggered.", Debug::INFO, options);
    QString style;
    ui->LogModeLbl->setEnabled((bool)NewState);
    ui->LogModeBox->setEnabled((bool)NewState);
    if(NewState == 0)
    {
        style = "color:grey";
    }
    else
    {
        style = "";
    }
    ui->LogModeBox->setStyleSheet(style);
    ui->LogModeLbl->setStyleSheet(style);

    this->options->SetAdvancedOptions(NewState >> 1);
}
void OptionDialog::LoggingMode_IndexChanged(int NewIndex)
{
    Debug::Log("LoggingMode_IndexChanged slot triggered.", Debug::INFO, options);
    this->options->SetLogMode((Options::LogMode)NewIndex);
}
void OptionDialog::TooltipColor_IndexChanged(int NewIndex)
{
    Debug::Log("TooltipColor_IndexChanged slot triggered.", Debug::INFO, options);
}
void OptionDialog::UiModeBox_IndexChanged(int NewIndex)
{
    Debug::Log("UiModeBox_IndexChanged slot triggered.", Debug::INFO, options);
    QString style;
    if(NewIndex == Options::LIGHT)
    {
        style = "background:white; color: black";
    }
    else if(NewIndex == Options::DARK)
    {
        style = "background:rgb(50, 54, 60) ; color: white";
    }
    this->setStyleSheet(style);
}
void OptionDialog::SaveBtn_Clicked()
{
    Debug::Log("SaveBtn_Clicked slot triggered.", Debug::INFO, options);

    this->options->SetUiMode((Options::UiMode)ui->UiModeBox->currentIndex());
    this->options->SetTooltipColor((Options::TooltipColor)ui->TooltipBox->currentIndex());
    this->options->SetLogMode((Options::LogMode)ui->LogModeBox->currentIndex());
    this->options->SetAdvancedOptions((bool)(ui->DebugEnableCheckBox->checkState() >> 1));

    this->options->SaveConfig();
    this->close();
}
void OptionDialog::CancelBtn_Clicked()
{
    Debug::Log("CancelBtn_Clicked slot triggered.", Debug::INFO, options);
    this->close();
}
