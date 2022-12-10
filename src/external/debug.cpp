#include "debug.h"

void Debug::Log(const QString Message, LogLevel Severity, Options* options)
{
    switch(options->GetLogMode())
    {
        case Options::RELEASE:
            if(Severity == INFO) return;
            ConsolePrint(Message, Severity);
            LogFilePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        case Options::RELEASE_NOFILE:
            if(Severity == INFO) return;
            ConsolePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        case Options::DEV:
            ConsolePrint(Message, Severity);
            LogFilePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        case Options::DEV_NOFILE:
            ConsolePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        case Options::LOGMODE_COUNT:
        default:
            break;
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
    QFile logFile("./NeoStudio.log");
    logFile.open(QIODevice::Append);
    logFile.write(QDateTime::currentDateTime().toString().toUtf8() +
                                        " - " +
                                        logLevels[Severity].toUtf8() +
                                        Message.toUtf8() + "\n");
}
