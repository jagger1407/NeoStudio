#ifndef OPTIONS_H
#define OPTIONS_H

#include "src/external/qt_includes.h"
#include "src/external/cfgparser.h"

/**
 * @todo write docs
 */
class Options
{
public:

#define CONFIG_PATH "./options.cfg"

    typedef enum {
        LOGMODE,
        TOOLTIPCOLOR,
        UI_MODE,
        ADVANCED_OPTIONS,
        OPTION_COUNT
    } OptionType;
    QString OptionStr[4] =
    {
        "LogMode",
        "TooltipColor",
        "UiMode",
        "AdvancedOptions"
    };

    /**The log modes used to determine which log levels get printed.*/
    typedef enum{
    DEV,
    DEV_NOFILE,
    RELEASE,
    RELEASE_NOFILE,
    LOGMODE_COUNT
    } LogMode;
    QString LogmodeStr[4] = { "Dev", "Dev_Nofile", "Release", "Release_Nofile" };

    /**A selection of text color choices for tooltips.*/
    typedef enum {
    WHITE,
    BLACK,
    BLUE,
    RED,
    TOOLTIPCOLOR_COUNT
    } TooltipColor;
    QString TooltipStr[4] = { "White", "Black", "Blue", "Red" };


    /**A selection of background color choices for the entire program.*/
    typedef enum {
        LIGHT,
        DARK,
        UIMODE_COUNT
    } UiMode;
    QString UimodeStr[2] = { "Light", "Dark" };

#define DEFAULT_LOGMODE RELEASE_NOFILE
#define DEFAULT_TOOLTIPCOLOR BLACK
#define DEFAULT_UIMODE DARK
#define DEFAULT_ADVANCED_OPTIONS false

    Options();
    Options(LogMode log, TooltipColor tooltipCol, UiMode uiMode);
    void LoadDefaults(bool saveFile = false);
    bool LoadConfig();
    void SaveConfig();

    LogMode GetLogMode();
    void SetLogMode(LogMode newMode);

    QString GetStyledTooltip(QString tooltip);
    TooltipColor GetTooltipColor();
    void SetTooltipColor(TooltipColor newColor);

    UiMode GetUiMode();
    void SetUiMode(UiMode newMode);

    bool GetAdvancedOptions();
    void SetAdvancedOptions(bool value);

private:
    QString tooltipStyles[4] =
    {
            "<font color=\"white\">",
            "<font color=\"black\">",
            "<font color=\"blue\">",
            "<font color=\"red\">",
    };

    CfgParser* cfg;

    LogMode logMode;
    TooltipColor tooltipColor;
    UiMode uiMode;
    bool advancedOptions;
};

#endif // OPTIONS_H
