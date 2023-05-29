#ifndef CFGPARSER_H
#define CFGPARSER_H

#include "qt_includes.h"
#include "fileparse.h"

/**
 * Object to act as an intermediate between Neo Studio and .cfg files.
 * "Uhh why not .json" stfu I will never resort to that garbage
 */
class CfgParser
{
public:
    CfgParser(QString cfgPath);
    CfgParser();
    bool Add(QString parameter, QString value);
    bool Change(QString parameter, QString newValue);
    QString GetParameter(QString parameter);
    //bool remove(QString parameter);
    bool WriteConfig(QString cfgPath);

private:
    QMap<QString, QString>* parameters;
};

#endif // CFGPARSER_H

