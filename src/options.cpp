#include "options.h"

Options::Options()
{
    if(!FileParse::DoesFileExist(CONFIG_PATH))
        LoadDefaults(true);
    else LoadConfig();
}

#if 1 // unused
Options::Options(LogMode logMode,TooltipColor tooltipColor, UiMode uiMode)
{
    this->logMode = logMode;
    this->tooltipColor = tooltipColor;
    this->uiMode = uiMode;
    advancedOptions = false;
}
#endif

void Options::LoadDefaults(bool saveFile)
{
    cfg = new CfgParser();

    logMode = DEFAULT_LOGMODE;
    tooltipColor = DEFAULT_TOOLTIPCOLOR;
    uiMode = DEFAULT_UIMODE;
    advancedOptions = DEFAULT_ADVANCED_OPTIONS;

    cfg->add(OptionStr[LOGMODE], LogmodeStr[DEFAULT_LOGMODE]);
    cfg->add(OptionStr[TOOLTIPCOLOR], TooltipStr[DEFAULT_TOOLTIPCOLOR]);
    cfg->add(OptionStr[UI_MODE], UimodeStr[DEFAULT_UIMODE]);
    cfg->add(OptionStr[ADVANCED_OPTIONS], QString::number(DEFAULT_ADVANCED_OPTIONS));

    if(saveFile) cfg->WriteConfig(CONFIG_PATH);
}

bool Options::LoadConfig()
{
    if(!FileParse::DoesFileExist(CONFIG_PATH)) return false;
    cfg = new CfgParser(CONFIG_PATH);

    QString option = cfg->getParameter(OptionStr[LOGMODE]);
    for(int i=0;i<LOGMODE_COUNT;i++)
        if(option == LogmodeStr[i]) logMode = (LogMode)i;

    option = cfg->getParameter(OptionStr[TOOLTIPCOLOR]);
    for(int i=0;i<TOOLTIPCOLOR_COUNT;i++)
        if(option == TooltipStr[i]) tooltipColor = (TooltipColor)i;

    option = cfg->getParameter(OptionStr[UI_MODE]);
    for(int i=0;i<UIMODE_COUNT;i++)
        if(option == UimodeStr[i]) uiMode = (UiMode)i;

    option = cfg->getParameter(OptionStr[ADVANCED_OPTIONS]);
    advancedOptions = option.toUInt();

    return true;
}


void Options::SaveConfig()
{
    if(cfg == nullptr) return;

    cfg->change(OptionStr[LOGMODE], LogmodeStr[logMode]);
    cfg->change(OptionStr[TOOLTIPCOLOR], TooltipStr[tooltipColor]);
    cfg->change(OptionStr[UI_MODE], UimodeStr[uiMode]);
    cfg->change(OptionStr[ADVANCED_OPTIONS], QString::number(advancedOptions));

    cfg->WriteConfig(CONFIG_PATH);
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
