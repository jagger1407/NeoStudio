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
    QString OptionStr[OPTION_COUNT] = {
        "LogMode",
        "TooltipColor",
        "UiMode",
        "AdvancedOptions"
    };

    /**The log modes used to determine which log levels get printed.*/
    typedef enum {
    DEV,
    DEV_NOFILE,
    RELEASE,
    RELEASE_NOFILE,

    LOGMODE_COUNT
    } LogMode;
    QString LogmodeStr[LOGMODE_COUNT] = {
        "Dev",
        "Dev_Nofile",
        "Release",
        "Release_Nofile"
    };

    /**A selection of text color choices for tooltips.*/
    typedef enum {
    WHITE,
    BLACK,
    BLUE,
    RED,
    TOOLTIPCOLOR_COUNT
    } TooltipColor;
    QString TooltipStr[TOOLTIPCOLOR_COUNT] = {
        "White",
        "Black",
        "Blue",
        "Red"
    };

#define DEFAULT_LOGMODE RELEASE_NOFILE
#define DEFAULT_TOOLTIPCOLOR BLACK
#define DEFAULT_UIMODE "Dark"
#define DEFAULT_ADVANCED_OPTIONS false

    static void InitOptions();
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
/** This is a global Object housing the options.
 */
extern Options g_Options;

#endif // OPTIONS_H
