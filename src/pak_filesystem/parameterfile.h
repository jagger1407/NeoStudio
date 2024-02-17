#ifndef PARAMETERFILE_H
#define PARAMETERFILE_H

#include "src/external/qt_includes.h"
#include "src/bitmanipulation.h"
#include "src/neo_info.h"

/**
 * An inheritable class encompassing the Parameter Files inside a .pak
 */
class ParameterFile
{

public:

    /** This represents a parameter in the program.
     *
     *  offset = the offset used to access the parameter
     *  UiElement = the UI Element that edits this parameter
     */
    typedef struct
    {
        unsigned short offset;
        QObject* UiElement;
    } Param_Offset;

    /**Changes one specific flag within the parameter section.
     *
     * @param Offset The offset used to locate the parameter
     * @param bit The bit that this flag uses
     * @param Value The value you want this bit to have
     */
    void ChangeData(int Offset, int bit, bool Value)
    {
        BitManipulation::SetBit(fileData.data() + Offset, bit, Value);
    }
    /**Changes one specific byte within the parameter section.
     *
     * @param Offset The offset used to locate the parameter
     * @param Value The value you want this byte to have
     */
    void ChangeData(int Offset, unsigned char Value)
    {
        *(fileData.data() + Offset) = Value;
    }
    /**Changes one specific short (2 Bytes) within the parameter section.
     *
     * @param Offset The offset used to locate the parameter
     * @param Value The value you want this short to have
     */
    void ChangeData(int Offset, unsigned short Value)
    {
        *(unsigned short*)(fileData.data() + Offset) = Value;
    }
    /**Changes one specific int (2/4 Bytes) within the parameter section.
     *
     * @param Offset The offset used to locate the parameter
     * @param Value The value you want this int to have
     */
    void ChangeData(int Offset, int Value)
    {
        *(int*)(fileData.data() + Offset) = Value;
    }
    /**Changes one specific float (4 Bytes) within the parameter section.
     *
     * @param Offset The offset used to locate the parameter
     * @param Value The value you want this float to have
     */
    void ChangeData(int Offset, float Value)
    {
        *(float*)(fileData.data() + Offset) = Value;
    }
    /**Changes one specific long (4 Bytes) within the parameter section.
     *
     * @param Offset The offset used to locate the parameter
     * @param Value The value you want this long to have
     */
    void ChangeData(int Offset, unsigned long Value)
    {
        *(unsigned long*)(fileData.data() + Offset) = Value;
    }
    /**Returns the parameter type of this object.*/
    virtual ParameterType GetParameterType() { return PARAM_TYPE_INVALID; }
    /**Gets the Single-Byte parameter value of the parameter corresponding to the Object.*/
    virtual unsigned char GetUByteParameter(QSpinBox* Object) { return 0; }
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    virtual unsigned short GetUShortParameter(QSpinBox* Object) { return 0; }
    /**Gets the 4-Byte parameter value of the parameter corresponding to the Object.*/
    virtual int GetIntParameter(QSpinBox* Object) { return 0; }
    /**Gets the Float parameter value of the parameter corresponding to the Object.*/
    virtual float GetFloatParameter(QDoubleSpinBox* Object) { return 0; }
    /**Gets the 1-Bit parameter value of the parameter corresponding to the Object.*/
    virtual bool GetFlagParameter(QCheckBox* Object) { return 0; }
    /**Sets the Single-Byte parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetUByteParameter(QSpinBox* Object, unsigned char NewValue) {}
    /**Sets the 2-Byte parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetUShortParameter(QSpinBox* Object, unsigned short NewValue) {}
    /**Sets the 4-Byte parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetIntParameter(QSpinBox* Object, int NewValue) {}
    /**Sets the Float parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetFloatParameter(QDoubleSpinBox* Object, float NewValue) {}
    /**Sets the 1-Bit parameter value of the parameter corresponding to the Object to NewValue.*/
    virtual void SetFlagParameter(QCheckBox* Object, bool NewValue) {}
    /**Gets file data of this parameter file as a whole QByteArray.*/
    virtual QByteArray* GetFileData() { return nullptr; }
    /**Sets the entire parameter file data array at once to NewData, this should normally not be used.*/
    virtual void SetFileData(QByteArray NewData) { return; }
    /**Checks to see if the given QByteArray representing the parameter file data is empty.*/
    bool IsEmpty()
    { return fileData.isEmpty(); }
protected:
    /**The QByteArray that includes the data of the entire parameter file.*/
    QByteArray fileData;

};

#endif // PARAMETERFILE_H
