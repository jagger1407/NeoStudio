#include "fileparse.h"

QStringList FileParse::ReadLines(QString FilePath)
{
    Debug::Log("ReadLines called.", Debug::INFO);
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        Debug::Log("ReadLines: no file path given.", Debug::ERROR);
        return *new QStringList;
    }
    // Open file for reading, or prints error if it fails
    QFile file(FilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        Debug::Log("ReadLines: File couldn't be opened", Debug::ERROR);
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
    Debug::Log("ReadWholeFile called.", Debug::INFO);
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        Debug::Log("ReadWholeFile: no path given, returning empty QByteArray.", Debug::WARNING);
        return QByteArray();
    }
    // Open file for reading, or prints error if it fails
    QFile file(FilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        Debug::Log("ReadWholeFile: File " + FilePath + " couldn't be opened, returning empty QByteArray.", Debug::WARNING);
        return QByteArray();
    }
    QByteArray output(file.readAll());
    file.close();
    return output;
}
void FileParse::WriteFile(QString FilePath, QByteArray* Data)
{
    Debug::Log("WriteFile called.", Debug::INFO);
    QFile newFile(FilePath);
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        Debug::Log("WriteFile: No path given.", Debug::WARNING);
    }
    // Don't wanna corrupt the existing file, after all
    if(newFile.exists()) newFile.remove();

    newFile.open(QIODevice::ReadWrite);
    // Unlikely but you can't be too sure
    if(Data == nullptr)
    {
        Debug::Log("WriteFile: no data given.", Debug::ERROR);
        newFile.close();
        return;
    }
    newFile.write(*Data);
    newFile.close();
}
void FileParse::AppendLine(QString FilePath, QString line)
{
    Debug::Log("AppendLine called.", Debug::INFO);
    QFile currentFile(FilePath);
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        Debug::Log("AppendLine: No path given.", Debug::WARNING);
    }

    currentFile.open(QIODevice::Append);
    currentFile.write(line.toUtf8());
    currentFile.close();
}
bool FileParse::DoesFileExist(QString FilePath)
{
    return QFile(FilePath).exists();
}

