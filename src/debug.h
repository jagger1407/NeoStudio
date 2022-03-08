#ifndef DEBUG_H
#define DEBUG_H

#include "qt_includes.h"
/**
 * Class to handle debug output
 */
class Debug
{
public:
    /**Prints message to console.*/
    static void ConsolePrint(const QString Message);
    /**Prints message to log file.*/
    static void LogFilePrint(const QString Message);
    /**Show message as error box to the user.*/
    static void ShowError(const QString Message);
};

#endif // DEBUG_H
