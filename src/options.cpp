#include "options.h"

Options::Options()
{
    if(!FileParse::DoesFileExist(CONFIG_PATH)) LoadDefaults(true);
    else LoadConfig();
}
Options::Options(LogMode logMode,TooltipColor tooltipColor, UiMode uiMode)
{
    this->logMode = logMode;
    this->tooltipColor = tooltipColor;
    this->uiMode = uiMode;
    advancedOptions = false;
}

void Options::LoadDefaults(bool saveFile)
{
    logMode = DEFAULT_LOGMODE;
    tooltipColor = DEFAULT_TOOLTIPCOLOR;
    uiMode = DEFAULT_UIMODE;
    advancedOptions = DEFAULT_ADVANCED_OPTIONS;

    if(saveFile) SaveConfig();
}

bool Options::LoadConfig()
{
    if(!FileParse::DoesFileExist(CONFIG_PATH)) return false;

    QStringList fileText = FileParse::ReadLines(CONFIG_PATH);
    for(QString line : fileText)
    {
        QStringList split = line.split(" = ");
        if(split[1].back() == '\n') split[1].truncate(split[1].size()-1);
        int option;
        QString value = "";
        for(int i=0;i<OPTION_COUNT;i++) if(split[0] == OptionStr[i])
        {
            value = split[1];
            option = i;
            break;
        }
        if(value == "") continue;

        switch(option)
        {
            case LOGMODE:
                for(int i=0; i<LOGMODE_COUNT;i++) if(value == LogmodeStr[i]) this->logMode = (LogMode)i;
                break;
            case TOOLTIPCOLOR:
                for(int i=0; i<TOOLTIPCOLOR_COUNT;i++) if(value == TooltipStr[i]) this->tooltipColor = (TooltipColor)i;
                break;
            case UI_MODE:
                for(int i=0; i<UIMODE_COUNT;i++) if(value == UimodeStr[i]) this->uiMode = (UiMode)i;
                break;
            case ADVANCED_OPTIONS:
                this->advancedOptions = value.toInt();
        }
    }
    return true;
}


void Options::SaveConfig()
{
    if(!FileParse::DoesFileExist(CONFIG_PATH)) QFile::remove(CONFIG_PATH);

    QByteArray optionText;

    optionText += (OptionStr[LOGMODE] + " = " + LogmodeStr[logMode] + "\n").toUtf8();
    optionText += (OptionStr[TOOLTIPCOLOR] + " = " + TooltipStr[tooltipColor] + "\n").toUtf8();
    optionText += (OptionStr[UI_MODE] + " = " + UimodeStr[uiMode] + "\n").toUtf8();
    optionText += (OptionStr[ADVANCED_OPTIONS] + " = " + ('0' + advancedOptions)).toUtf8();

    FileParse::WriteFile(CONFIG_PATH, &optionText);
}

Options::TooltipColor Options::GetTooltipColor()
{
     return tooltipColor;
}

void Options::SetTooltipColor(Options::TooltipColor newColor)
{
    if(newColor == TOOLTIPCOLOR_COUNT) return;
    this->tooltipColor = newColor;
}

QString Options::GetStyledTooltip(QString tooltip)
{
    if(tooltip.isEmpty()) return tooltip;
    if(!tooltip.contains("<")) return tooltipStyles[this->tooltipColor] + tooltip + "</font>";
    QStringList text = tooltip.split(">");
    QString line = "";
    for(QString el : text)
    {
        if(!el.startsWith("<"))
        {
            line = el.split("<")[0];
            break;
        }
    }
    return tooltipStyles[this->tooltipColor] + line + "</font>";
}

Options::LogMode Options::GetLogMode()
{
    return logMode;
}

void Options::SetLogMode(Options::LogMode newMode)
{
    if(newMode == LOGMODE_COUNT) return;
    this->logMode = newMode;
}

Options::UiMode Options::GetUiMode()
{
    return uiMode;
}

void Options::SetUiMode(Options::UiMode newMode)
{
    if(newMode == UIMODE_COUNT) return;
    uiMode = newMode;
}


bool Options::GetAdvancedOptions()
{
    return advancedOptions;
}
void Options::SetAdvancedOptions(bool value)
{
    this->advancedOptions = value;
}
