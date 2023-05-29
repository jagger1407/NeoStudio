#include "cfgparser.h"

CfgParser::CfgParser(QString cfgPath)
{
    parameters = new QMap<QString, QString>();

    QStringList lines = FileParse::ReadLines(cfgPath);
    if(lines.isEmpty())
    {
        return;
    }

    QStringList temp;
    for(QString line : lines)
    {
        // # signals a comment, to be ignored
        // if not a parameter line, to be ignored
        // dunno when I'll properly implement this,
        // but for now it'll just be an option.
        if(line.startsWith("#") || !line.contains("=")) continue;
        line.replace(' ', "");
        line.replace('\n', "");
        // put all parameters into the QMap
        temp = line.split("=");
        parameters->insert(temp[0], temp[1]);
    }
}

CfgParser::CfgParser()
{
    parameters = new QMap<QString, QString>();
}

bool CfgParser::Add(QString parameter, QString value)
{
    if(parameters == nullptr || parameters->contains(parameter)) return false;
    parameters->insert(parameter, value);
    return true;
}

bool CfgParser::Change(QString parameter, QString newValue)
{
    if(parameters == nullptr || !parameters->contains(parameter)) return false;
    (*parameters)[parameter] = newValue;
    return true;
}

QString CfgParser::GetParameter(QString parameter)
{
    if(parameters == nullptr || !parameters->contains(parameter)) return NULL;
    return (*parameters)[parameter];
}

bool CfgParser::WriteConfig(QString cfgPath)
{
    if(parameters == nullptr) return false;
    QByteArray outputData;
    for(QString key : parameters->keys())
    {
        outputData += (key + " = " + (*parameters)[key] + "\n").toUtf8();
    }
    FileParse::WriteFile(cfgPath, &outputData);
    return true;
}
