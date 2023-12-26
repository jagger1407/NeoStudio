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

#define DEFAULT_LOGMODE RELEASE_NOFILE
#define DEFAULT_TOOLTIPCOLOR BLACK
#define DEFAULT_UIMODE "Dark"
#define DEFAULT_ADVANCED_OPTIONS false

    Options();
    Options(LogMode log, TooltipColor tooltipCol, QString uiMode);
    void LoadDefaults(bool saveFile = false);
    bool LoadConfig();
    void SaveConfig();

    QString GetStyledTooltip(QString tooltip);

    LogMode logMode;
    TooltipColor tooltipColor;
    QString uiMode;
    bool advancedOptions;

private:
    QString tooltipStyles[4] =
    {
            "<font color=\"white\">",
            "<font color=\"black\">",
            "<font color=\"blue\">",
            "<font color=\"red\">",
    };

    CfgParser* cfg;
};

#endif // OPTIONS_H
