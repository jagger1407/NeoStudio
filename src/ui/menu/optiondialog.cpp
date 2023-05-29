#include "optiondialog.h"

OptionDialog::OptionDialog(Options* options)
    : ui(new Ui::OptionDialog), options(options)
{
    initializing = true;
    int logMode = this->options->GetLogMode();
    QString uiMode = this->options->GetUiMode();
    int tool = this->options->GetTooltipColor();
    bool advanced = this->options->GetAdvancedOptions();
    ui->setupUi(this);
    ReloadUIsBtn_Clicked();
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + options->GetUiMode() + ".qss"));
    this->setWindowTitle("Options");
    this->setWindowIcon(QIcon("./assets/cog-wheel.png"));

    ui->LogModeBox->setCurrentIndex(logMode);
    ui->TooltipBox->setCurrentIndex(tool);
    ui->UiModeBox->setCurrentText(uiMode);
    ui->DebugEnableCheckBox->setCheckState((Qt::CheckState)(advanced << 1));

    if(!advanced)
    {
        ui->LogModeBox->setStyleSheet("color:grey");
        ui->LogModeLbl->setStyleSheet("color:grey");
    }

    initializing = false;
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
    this->options->SetTooltipColor((Options::TooltipColor)NewIndex);
}
void OptionDialog::UiModeBox_IndexChanged(int NewIndex)
{
    if(initializing) return;
    Debug::Log("UiModeBox_IndexChanged slot triggered.", Debug::INFO, options);
    QString style = ui->UiModeBox->currentText();
    this->options->SetUiMode(style);
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + style +".qss"));
}
void OptionDialog::ReloadUIsBtn_Clicked()
{
    initializing = true;
    QDir uiDir("./assets/ui");
    ui->UiModeBox->clear();
    for(QString style : uiDir.entryList())
    {
        if(!style.contains(".qss")) continue;
        style.replace(".qss", "");
        ui->UiModeBox->addItem(style);
    }
    ui->UiModeBox->setCurrentText(options->GetUiMode());
    initializing = false;
}
void OptionDialog::SaveBtn_Clicked()
{
    Debug::Log("SaveBtn_Clicked slot triggered.", Debug::INFO, options);

    this->options->SetUiMode(ui->UiModeBox->currentText());
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
