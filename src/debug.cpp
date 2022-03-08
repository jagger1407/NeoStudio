#include "debug.h"

void Debug::ConsolePrint(const QString Message)
{
    qDebug().noquote() << Message;
}
void Debug::ShowError(const QString Message)
{
    QMessageBox ErrorWindow;
    ErrorWindow.setWindowTitle("Error!");
    ErrorWindow.setText(Message);
    ErrorWindow.exec();
}
void Debug::LogFilePrint(const QString Message)
{
    QFile logFile("../Neo Studio.log");
    logFile.open(QIODevice::Append);
    if(logFile.size() > 0) logFile.write("\n" + Message.toUtf8());
    else logFile.write(Message.toUtf8());
}
