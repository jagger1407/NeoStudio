#include "optiondialog.h"

OptionDialog::OptionDialog()
    : ui(new Ui::OptionDialog)
{
    initializing = true;

    ui->setupUi(this);
    ReloadUIsBtn_Clicked();
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));
    this->setWindowTitle("Options");
    this->setWindowIcon(QIcon("./assets/cog-wheel.png"));

    ui->LogModeBox->setCurrentIndex(g_Options.logMode);
    ui->TooltipBox->setCurrentIndex(g_Options.tooltipColor);
    ui->UiModeBox->setCurrentText(g_Options.uiMode);
    ui->DebugEnableCheckBox->setCheckState((Qt::CheckState)(g_Options.advancedOptions << 1));

    if(!g_Options.advancedOptions)
    {
        ui->LogModeBox->setStyleSheet("color:grey");
        ui->LogModeLbl->setStyleSheet("color:grey");
    }

    initializing = false;
    Debug::Log("OptionDialog constructed.", Debug::INFO);
}

void OptionDialog::DebugEnableCheckState_Changed(int NewState)
{
    if(initializing) return;
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

    g_Options.advancedOptions = NewState >> 1;
}
void OptionDialog::LoggingMode_IndexChanged(int NewIndex)
{
    if(initializing) return;
    Debug::Log("LoggingMode_IndexChanged slot triggered.", Debug::INFO);
    g_Options.logMode = (Options::LogMode)NewIndex;
}
void OptionDialog::TooltipColor_IndexChanged(int NewIndex)
{
    if(initializing) return;
    Debug::Log("TooltipColor_IndexChanged slot triggered.", Debug::INFO);
    g_Options.tooltipColor = (Options::TooltipColor)NewIndex;
}
void OptionDialog::UiModeBox_IndexChanged(int NewIndex)
{
    if(initializing) return;
    Debug::Log("UiModeBox_IndexChanged slot triggered.", Debug::INFO);
    QString style = ui->UiModeBox->currentText();
    g_Options.uiMode = style;
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
    ui->UiModeBox->setCurrentText(g_Options.uiMode);
    initializing = false;
}
void OptionDialog::SaveBtn_Clicked()
{
    if(initializing) return;
    Debug::Log("SaveBtn_Clicked slot triggered.", Debug::INFO);

    g_Options.uiMode = ui->UiModeBox->currentText();
    g_Options.tooltipColor = (Options::TooltipColor)ui->TooltipBox->currentIndex();
    g_Options.logMode = (Options::LogMode)ui->LogModeBox->currentIndex();
    g_Options.advancedOptions = (bool)(ui->DebugEnableCheckBox->checkState() >> 1);

    g_Options.SaveConfig();
    this->close();
}
void OptionDialog::CancelBtn_Clicked()
{
    if(initializing) return;
    Debug::Log("CancelBtn_Clicked slot triggered.", Debug::INFO);
    this->close();
}
