#include "fileparse.h"

QStringList FileParse::ReadLines(QString FilePath)
{
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        return QStringList();
    }
    // Open file for reading, returns if it fails
    QFile file(FilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return QStringList();
    }
    // Read each line and add it to a QStringList
    QStringList FileText;
    while(!file.atEnd())
    { 
        FileText << file.readLine().replace("\r", "").replace("\n", "\0");
    }
    file.close();
    return FileText;
}
QByteArray FileParse::ReadWholeFile(QString FilePath)
{
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        return QByteArray();
    }
    // Open file for reading, or prints error if it fails
    QFile file(FilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return QByteArray();
    }
    QByteArray output(file.readAll());
    file.close();
    return output;
}
void FileParse::WriteFile(QString FilePath, QByteArray* Data)
{
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        return;
    }

    FilePath = FilePath.replace("\r", "").replace("\n", "\0");
    QFile newFile(FilePath);

    // Don't wanna corrupt the existing file, after all
    if(newFile.exists()) newFile.remove();

    newFile.open(QIODevice::ReadWrite);
    // Unlikely but you can't be too sure
    if(Data == nullptr)
    {
        newFile.close();
        return;
    }
    newFile.write(*Data);
    newFile.close();
}
void FileParse::AppendLine(QString FilePath, QString line)
{
    QFile currentFile(FilePath);
    // Check FilePath if it even has a value
    if(FilePath == "")
    {
        return;
    }

    currentFile.open(QIODevice::Append);
    currentFile.write(line.toUtf8());
    currentFile.close();
}
bool FileParse::DoesFileExist(QString FilePath)
{
    return QFile(FilePath).exists();
}

