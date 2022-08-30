#ifndef FILEPARSE_H
#define FILEPARSE_H

#include "qt_includes.h"
#include "debug.h"
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
};

#endif // FILEPARSE_H
