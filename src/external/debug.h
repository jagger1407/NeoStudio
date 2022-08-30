#ifndef DEBUG_H
#define DEBUG_H

#include "qt_includes.h"
/**
 * Class to handle debug output
 */
class Debug
{
public:
    /**Each log level used.*/
    typedef enum{
        INFO,
        WARNING,
        ERROR
    } LogLevel;
    /**The log modes used to determine which log levels get printed.*/
    typedef enum{
        DEV,
        DEV_NOFILE,
        RELEASE,
        RELEASE_NOFILE
    } LogMode;
    /**The Logging mode decides if you'll get logs of type INFO as well as the rest.*/
    static LogMode CurrentLogMode;
    /**Generic Logging Function*/
    static void Log(const QString Message, LogLevel Severity);
    /**Prints message to console.*/
    static void ConsolePrint(const QString Message, LogLevel Severity);
    /**Prints message to log file.*/
    static void LogFilePrint(const QString Message, LogLevel Severity);
    /**Show message as error box to the user.*/
    static void ShowError(const QString Message);
};

#endif // DEBUG_H
