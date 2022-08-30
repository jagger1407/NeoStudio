#include "debug.h"

void Debug::Log(const QString Message, LogLevel Severity)
{
    switch(CurrentLogMode)
    {
        case RELEASE:
        {
            if(Severity == INFO) return;
            ConsolePrint(Message, Severity);
            LogFilePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        }
        case RELEASE_NOFILE:
        {
            if(Severity == INFO) return;
            ConsolePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        }
        case DEV:
        {
            ConsolePrint(Message, Severity);
            LogFilePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        }
        case DEV_NOFILE:
        {
            ConsolePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        }
    }
}
void Debug::ConsolePrint(const QString Message, LogLevel Severity)
{
    QString logLevels[3] = { "Info: ", "Warning: ", "ERROR! " };
    qDebug().noquote() << QDateTime::currentDateTime().toString() << " - " + logLevels[Severity] << Message;
}
void Debug::ShowError(const QString Message)
{
    QMessageBox ErrorWindow;
    ErrorWindow.setWindowTitle("Error!");
    ErrorWindow.setText(Message);
    ErrorWindow.exec();
}
void Debug::LogFilePrint(const QString Message, LogLevel Severity)
{
    QString logLevels[3] = { "Info: ", "Warning: ", "ERROR! " };
    QFile logFile("../Neo Studio.log");
    logFile.open(QIODevice::Append);
    if(logFile.size() == 0) logFile.write(QDateTime::currentDateTime().toString().toUtf8() +
                                        " - " +
                                        logLevels[Severity].toUtf8() +
                                        Message.toUtf8());
    else logFile.write("\n" +
                        QDateTime::currentDateTime().toString().toUtf8() +
                        " - " +
                        logLevels[Severity].toUtf8() +
                        Message.toUtf8());
}
