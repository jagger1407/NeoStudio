#include "fileparse.h"

QStringList FileParse::ReadLines(QString FilePath)
{
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        Debug::ConsolePrint("Error! ReadFile(): FilePath empty");
        return *new QStringList;
    }
    // Open file for reading, or prints error if it fails
    QFile file(FilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        Debug::ConsolePrint("Error! ReadFile(): File couldn't be opened");
        return *new QStringList;
    }
    // Read each line and add it to a QStringList
    QStringList FileText;
    while(!file.atEnd())
    {
        FileText << file.readLine();
    }
    file.close();
    return FileText;
}
QByteArray FileParse::ReadWholeFile(QString FilePath)
{
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        Debug::ConsolePrint("Error! ReadFile: no path given, returning empty QByteArray.");
        return QByteArray();
    }
    // Open file for reading, or prints error if it fails
    QFile file(FilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        Debug::ConsolePrint("Error! ReadFile: File " + FilePath + " couldn't be opened, returning empty QByteArray.");
        return QByteArray();
    }
    QByteArray output(file.readAll());
    file.close();
    return output;
}
void FileParse::WriteFile(QString FilePath, QByteArray* Data)
{
    // Don't wanna corrupt the existing file, after all
    if(QFile(FilePath).exists()) QFile(FilePath).remove();

    QFile newFile(FilePath);
    newFile.open(QIODevice::ReadWrite);
    // Unlikely but you can't be too sure
    if(Data == nullptr)
    {
        Debug::ConsolePrint("Error! WriteFile: no data given.");
        newFile.close();
        return;
    }
    newFile.write(*Data);
    newFile.close();
}
