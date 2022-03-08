#ifndef PAKCONTROLS_H
#define PAKCONTROLS_H

#include "fileparse.h"
#include "neo_info.h"

/**
 * Object to handle and parse .pak files
 */
class PakControls
{
public:
    /**
     * Constructs a new PakControls object and connects it to given .pak file.
     */
    PakControls(QString FilePath);
    /**Checks if the PakControls object is connected to a .pak file.*/
    bool HasFailed();
    /**Updates .pak Data with current parameters and saves data to Path.*/
    void SavePak(QString Path);
    /**Returns whole pak file as a QByteArray.*/
    QByteArray GetPakData();
    /**Returns specific parameter section as a QByteArray.*/
    QByteArray GetParamData(Parameter ParamType);
    /**Updates specific parameter array with Data.*/
    void UpdateParamData(Parameter ParamType, QByteArray Data);
private:
    QByteArray LeftPak;
    QByteArray RightPak;
    QByteArray paramData[4];
    int paramOffset[5];
    int paramSize[4];
    bool failed = true;
};

#endif // PAKCONTROLS_H
