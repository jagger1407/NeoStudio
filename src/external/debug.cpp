#include "debug.h"

void Debug::Log(const QString Message, LogLevel Severity)
{
    switch(g_Options.logMode)
    {
        case Options::RELEASE:
            if(Severity <= INFO) return;
            ConsolePrint(Message, Severity);
            LogFilePrint(Message, Severity);
            if(Severity == ERROR) ShowError(Message);
            break;
        case Options::RELEASE_NOFILE:
            if(Severity <= INFO) return;
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
    QString logLevels[LOGLEVEL_SIZE] = { "", "Info: ", "Warning: ", "ERROR! " };
    if(Severity < INFO)
        qInfo().noquote() << Message;
    else
        qInfo().noquote() << QDateTime::currentDateTime().toString() << " - " + logLevels[Severity] << Message;
}
void Debug::ShowError(const QString Message)
{
    QMessageBox ErrorWindow;
    ErrorWindow.setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));
    ErrorWindow.setWindowTitle("Error!");
    ErrorWindow.setText(Message);
    QPushButton* okBtn = new QPushButton("OK");
    okBtn->setMinimumSize(QSize(50, 25));
    ErrorWindow.addButton(okBtn, QMessageBox::AcceptRole);
    ErrorWindow.exec();
    delete okBtn;
}
void Debug::LogFilePrint(const QString Message, LogLevel Severity)
{
    QString logLevels[LOGLEVEL_SIZE] = { "", "Info: ", "Warning: ", "ERROR! " };
    QFile logFile("./NeoStudio.log");
    logFile.open(QIODevice::Append);
    logFile.write(QDateTime::currentDateTime().toString().toUtf8() +
                                        " - " +
                                        logLevels[Severity].toUtf8() +
                                        Message.toUtf8() + "\n");
}
