#ifndef PARAMETERFILE_H
#define PARAMETERFILE_H

#include "src/external/qt_includes.h"
#include "src/neo_info.h"

/**
 * An inheritable class encompassing the Parameter Files inside a .pak
 */
class ParameterFile
{

public:
#define param_offset const unsigned char
    void ChangeData(int Offset, unsigned char Value)
    {
        fileData.data()[Offset] = Value;
    }
    void ChangeData(int Offset, unsigned short Value)
    {
        *(unsigned short*)(fileData.data() + Offset) = Value;
    }
    void ChangeData(int Offset, int Value)
    {
        *(int*)(fileData.data() + Offset) = Value;
    }
    void ChangeData(int Offset, float Value)
    {
        *(float*)(fileData.data() + Offset) = Value;
    }
    void ChangeData(int Offset, unsigned long Value)
    {
        *(unsigned long*)(fileData.data() + Offset) = Value;
    }
    virtual ParameterType GetParameterType() { return (ParameterType)0; }
    /**Gets the Single-Byte parameter value of the parameter corresponding to the Object.*/
    virtual unsigned char GetUByteParameter(QString ObjectName) { return 0; }
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    virtual unsigned short GetUShortParameter(QString ObjectName) { return 0; }
    /**Gets the 4-Byte parameter value of the parameter corresponding to the Object.*/
    virtual int GetIntParameter(QString ObjectName) { return 0; }
    /**Gets the Float parameter value of the parameter corresponding to the Object.*/
    virtual float GetFloatParameter(QString ObjectName) { return 0; }
    /**Gets the 1-Bit parameter value of the parameter corresponding to the Object.*/
    virtual bool GetFlagParameter(QString ObjectName) { return 0; }
    /**Sets the Single-Byte parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetUByteParameter(QString ObjectName, unsigned char NewValue) {}
    /**Sets the 2-Byte parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetUShortParameter(QString ObjectName, unsigned short NewValue) {}
    /**Sets the 4-Byte parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetIntParameter(QString ObjectName, int NewValue) {}
    /**Sets the Float parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetFloatParameter(QString ObjectName, float NewValue) {}
    /**Sets the 1-Bit parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetFlagParameter(QString ObjectName, bool NewValue) {}
    /**Checks to see if the given QByteArray representing the parameter file data is empty.*/
    bool IsEmpty()
    { return fileData.isEmpty(); }
    /**Gets file data of this parameter file as a whole QByteArray.*/
    virtual QByteArray GetFileData() { return 0; }
    /**Sets the entire parameter file data array at once to NewData, this should normally not be used.*/
    virtual void SetFileData(QByteArray NewData) {}
protected:
    /**The QByteArray that includes the data of the entire parameter file.*/
    QByteArray fileData;
};

#endif // PARAMETERFILE_H
