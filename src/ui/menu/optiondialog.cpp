#include "optiondialog.h"

OptionDialog::OptionDialog()
    : ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Options");
    this->setWindowIcon(QIcon("./assets/cog-wheel.png"));
    ui->LogModeBox->setCurrentIndex(OptionProcessing::GetOption("LogMode"));
    ui->TooltipBox->setCurrentIndex(OptionProcessing::GetOption("TooltipColor"));
    ui->UiModeBox->setCurrentIndex(OptionProcessing::GetOption("UiMode"));
    if(ui->UiModeBox->currentIndex() == OptionProcessing::LIGHT)
    {
        this->setStyleSheet("background:white; color: black");
    }
    else if(ui->UiModeBox->currentIndex() == OptionProcessing::DARK)
    {
        this->setStyleSheet("background:rgb(50, 54, 60) ; color: white");
    }
    ui->LogModeBox->setStyleSheet("color:grey");
    ui->LogModeLbl->setStyleSheet("color:grey");


    Debug::Log("OptionDialog constructed.", Debug::INFO);
}

void OptionDialog::DebugEnableCheckState_Changed(int NewState)
{
    Debug::Log("DebugEnableCheckState_Changed slot triggered.", Debug::INFO);
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
}
void OptionDialog::LoggingMode_IndexChanged(int NewIndex)
{
    Debug::Log("LoggingMode_IndexChanged slot triggered.", Debug::INFO);
}
void OptionDialog::TooltipColor_IndexChanged(int NewIndex)
{
    Debug::Log("TooltipColor_IndexChanged slot triggered.", Debug::INFO);
}
void OptionDialog::SaveBtn_Clicked()
{
    Debug::Log("SaveBtn_Clicked slot triggered.", Debug::INFO);
    OptionProcessing::SaveConfigFile(ui->LogModeBox->currentIndex(), ui->TooltipBox->currentIndex(), ui->UiModeBox->currentIndex());
    this->close();
}
void OptionDialog::CancelBtn_Clicked()
{
    Debug::Log("CancelBtn_Clicked slot triggered.", Debug::INFO);
    this->close();
}

