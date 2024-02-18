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
    PakControls(QString FilePath);
    /**Checks if the PakControls object is connected to a .pak file.*/
    bool HasFailed();
    /**Updates .pak Data with current parameters and saves data to Path.*/
    void SavePak(QString Path);

    QByteArray GetParamData(int sectionID);

    void UpdateParamData(int sectionID, QByteArray* newData);

    // Will be part of the Options soon
    const QString sectionNameFile = "./assets/pak-sections.txt";
private:

    unsigned int offsets[PAK_SUB_COUNT + 1];
    QByteArray pakData;

    /**bool to check if the construction of the PakControls object failed.*/
    bool failed = true;
};

#endif // PAKCONTROLS_H
