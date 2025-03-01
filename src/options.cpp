#include "options.h"

Options g_Options;

void Options::InitOptions()
{
    if(!FileParse::DoesFileExist(CONFIG_PATH))
        g_Options.LoadDefaults(true);
    else g_Options.LoadConfig();
}

void Options::LoadDefaults(bool saveFile)
{
    this->cfg = new CfgParser();

    this->logMode = DEFAULT_LOGMODE;
    this->tooltipColor = DEFAULT_TOOLTIPCOLOR;
    this->uiMode = DEFAULT_UIMODE;
    this->advancedOptions = DEFAULT_ADVANCED_OPTIONS;
    this->sectionNameFile = DEFAULT_SECTION_FILE;

    this->cfg->Add(OptionStr[LOGMODE], LogmodeStr[DEFAULT_LOGMODE]);
    this->cfg->Add(OptionStr[TOOLTIPCOLOR], TooltipStr[DEFAULT_TOOLTIPCOLOR]);
    this->cfg->Add(OptionStr[UI_MODE], DEFAULT_UIMODE);
    this->cfg->Add(OptionStr[ADVANCED_OPTIONS], QString::number(DEFAULT_ADVANCED_OPTIONS));
    this->cfg->Add(OptionStr[SECTION_NAME_FILE], DEFAULT_SECTION_FILE);

    if(saveFile) this->cfg->WriteConfig(CONFIG_PATH);
}

bool Options::LoadConfig()
{
    if(!FileParse::DoesFileExist(CONFIG_PATH)) return false;
    this->cfg = new CfgParser(CONFIG_PATH);

    QString option = this->cfg->GetParameter(OptionStr[LOGMODE]);
    if(option.isEmpty()) option = LogmodeStr[DEFAULT_LOGMODE];
    for(int i=0;i<LOGMODE_COUNT;i++)
        if(option == LogmodeStr[i]) this->logMode = (LogMode)i;
    option = "";

    option = cfg->GetParameter(OptionStr[TOOLTIPCOLOR]);
    if(option.isEmpty()) option = TooltipStr[DEFAULT_TOOLTIPCOLOR];
    for(int i=0;i<TOOLTIPCOLOR_COUNT;i++)
        if(option == TooltipStr[i]) this->tooltipColor = (TooltipColor)i;
    option = "";

    this->uiMode = cfg->GetParameter(OptionStr[UI_MODE]);
    if(uiMode.isEmpty()) uiMode = DEFAULT_UIMODE;

    option = cfg->GetParameter(OptionStr[ADVANCED_OPTIONS]);
    if(option.isEmpty()) option = QString::number(DEFAULT_ADVANCED_OPTIONS);
    this->advancedOptions = option.toUInt();
    option = "";

    option = cfg->GetParameter(OptionStr[SECTION_NAME_FILE]);
    if(option.isEmpty()) option = DEFAULT_SECTION_FILE;
    sectionNameFile = option;

    return true;
}


void Options::SaveConfig()
{
    if(cfg == nullptr) return;

    cfg->Change(OptionStr[LOGMODE], LogmodeStr[logMode]);
    cfg->Change(OptionStr[TOOLTIPCOLOR], TooltipStr[tooltipColor]);
    cfg->Change(OptionStr[UI_MODE], uiMode);
    cfg->Change(OptionStr[ADVANCED_OPTIONS], QString::number(advancedOptions));
    cfg->Change(OptionStr[SECTION_NAME_FILE], sectionNameFile);

    cfg->WriteConfig(CONFIG_PATH);
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
