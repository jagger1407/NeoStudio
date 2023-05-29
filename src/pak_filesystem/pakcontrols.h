#ifndef PAKCONTROLS_H
#define PAKCONTROLS_H

#include "src/external/fileparse.h"
#include "src/external/debug.h"
#include "src/neo_info.h"

/**
 * Object to handle and parse .pak files
 */
class PakControls
{
public:
    /**
     * Constructs a new PakControls object and connects it to given .pak file.
     */
    PakControls(QString FilePath, Options* options);
    /**Checks if the PakControls object is connected to a .pak file.*/
    bool HasFailed();
    /**Updates .pak Data with current parameters and saves data to Path.*/
    void SavePak(QString Path);
    /**Returns whole pak file as a QByteArray.*/
    QByteArray GetPakData();
    /**Returns specific parameter section as a QByteArray.*/
    QByteArray GetParamData(ParameterType ParamType);
    /**Updates specific parameter array with Data.*/
    void UpdateParamData(ParameterType ParamType, QByteArray Data);
private:
    /**QByteArray containing everything that comes before the general parameters.*/
    QByteArray LeftPak;
    /**QByteArray containing everything that comes after the last known parameter type (Movement).*/
    QByteArray RightPak;
    /**QByteArray array containing the data for each respective parameter type.*/
    QByteArray paramData[4];
    /**int array containing the offsets needed to get to each parameter data section.*/
    int paramOffset[5];
    /**int array containing the size of each parameter section.*/
    int paramSize[4];
    /**bool to check if the construction of the PakControls object failed.*/
    bool failed = true;

    Options* options = nullptr;
};

#endif // PAKCONTROLS_H
