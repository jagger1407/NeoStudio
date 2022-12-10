#ifndef DEBUG_H
#define DEBUG_H

#include "qt_includes.h"
#include "src/options.h"


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
    /**Generic Logging Function*/
    static void Log(const QString Message, LogLevel Severity, Options* options);
    /**Prints message to console. Should not be used, use Debug::Log instead.*/
    static void ConsolePrint(const QString Message, LogLevel Severity);
    /**Prints message to log file. Should not be used, use Debug::Log instead.*/
    static void LogFilePrint(const QString Message, LogLevel Severity);
    /**Show message as error box to the user.*/
    static void ShowError(const QString Message);
};

#endif // DEBUG_H
