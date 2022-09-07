#ifndef OPTIONPROCESSING_H
#define OPTIONPROCESSING_H

#include "qt_includes.h"

class OptionProcessing
{
public:
    /**The log modes used to determine which log levels get printed.*/
    typedef enum{
    DEV,
    DEV_NOFILE,
    RELEASE,
    RELEASE_NOFILE
    } LogMode;
    /**A selection of text color choices for tooltips.*/
    typedef enum {
    WHITE,
    BLACK,
    BLUE,
    RED
    } TooltipColor;
    /**A selection of background color choices for the entire program.*/
    typedef enum {
        LIGHT,
        DARK
    } UiMode;

#define CONFIG_PATH "./options.cfg"
#define DEFAULT_LOGMODE RELEASE_NOFILE
#define DEFAULT_TOOLTIPCOLOR BLACK
#define DEFAULT_UIMODE DARK

    // Methods to Read/Save/Change Options
    static unsigned char GetOption(QString OptionName)
    {
        QFile* configFile = new QFile(CONFIG_PATH);
        if(!configFile->exists()) return (unsigned char)0xFF;
        configFile->open(QIODevice::ReadOnly);

        QStringList options;
        while(!configFile->atEnd())
        {
            options << configFile->readLine();
        }

        if(OptionName == "LogMode")
        {
            QString line;
            int i = 0;
            while(!line.contains("LogMode"))
            {
                line = options[i];
                i++;
            }
            line = line.split(' ').last();
            line.truncate(line.count() - 1);
            if(line == "Dev") return (unsigned char)DEV;
            else if(line == "Dev_NoFile") return (unsigned char)DEV_NOFILE;
            else if(line == "Release") return (unsigned char)RELEASE;
            else if(line == "Release_NoFile") return (unsigned char)RELEASE_NOFILE;
            else return (unsigned char)0xFF;
        }
        else if(OptionName == "TooltipColor")
        {
            QString line;
            int i = 0;
            while(!line.contains("TooltipColor"))
            {
                line = options[i];
                i++;
            }
            line = line.split(' ').last();
            line.truncate(line.count() - 1);
            if(line == "White") return (unsigned char)WHITE;
            else if(line == "Black") return (unsigned char)BLACK;
            else if(line == "Blue") return (unsigned char)BLUE;
            else if(line == "Red") return (unsigned char)RED;
            else return (unsigned char)0xFF;
        }
        else if(OptionName == "UiMode")
        {
            QString line;
            int i = 0;
            while(!line.contains("UiMode"))
            {
                line = options[i];
                i++;
            }
            line = line.split(' ').last();
            line.truncate(line.count() - 1);
            if(line == "LightMode") return (unsigned char)LIGHT;
            else if(line == "DarkMode") return (unsigned char)DARK;
            else return (unsigned char)0xFF;
        }
        else return (unsigned char)0xFF;
    }
    static void SaveConfigFile(unsigned char Log_Mode, unsigned char Tooltip_Color, unsigned char Ui_Mode)
    {
        QFile* configFile = new QFile(CONFIG_PATH);
        if(configFile->exists()) configFile->remove();
        configFile->open(QIODevice::ReadWrite);

        QString line = "LogMode = ";
        switch((LogMode)Log_Mode)
        {
            case DEV:
                line.append("Dev");
                break;
            case DEV_NOFILE:
                line.append("Dev_NoFile");
                break;
            case RELEASE:
                line.append("Release");
                break;
            case RELEASE_NOFILE:
                line.append("Release_NoFile");
        }
        configFile->write(line.toUtf8() + "\n");
        line = "TooltipColor = ";
        switch((TooltipColor)Tooltip_Color)
        {
            case WHITE:
                line.append("White");
                break;
            case BLACK:
                line.append("Black");
                break;
            case BLUE:
                line.append("Blue");
                break;
            case RED:
                line.append("Red");
        }
        configFile->write(line.toUtf8() + "\n");
        line = "UiMode = ";
        switch((UiMode)Ui_Mode)
        {
            case LIGHT:
                line.append("LightMode");
                break;
            case DARK:
                line.append("DarkMode");
        }
        configFile->write(line.toUtf8() + "\n");
        configFile->close();
    }
};


#endif //OPTIONPROCESSING_H
