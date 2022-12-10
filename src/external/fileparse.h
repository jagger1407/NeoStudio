#ifndef FILEPARSE_H
#define FILEPARSE_H

#include "qt_includes.h"
/**
 * Parse data from/to an external file.
 */
class FileParse
{
public:
    /**Returns contents of given file as a QStringList.*/
    static QStringList ReadLines(QString FilePath);
    /**Returns contents of given file as a QByteArray.*/
    static QByteArray ReadWholeFile(QString FilePath);
    /**Writes specified data to file.*/
    static void WriteFile(QString FilePath, QByteArray* Data = nullptr);
    /**Appends a single line to a text-based file.*/
    static void AppendLine(QString FilePath, QString line);
    /**Checks to see if a File exists.*/
    static bool DoesFileExist(QString FilePath);
};

#endif // FILEPARSE_H
