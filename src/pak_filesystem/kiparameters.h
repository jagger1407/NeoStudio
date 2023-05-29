#ifndef KIPARAMETERS_H
#define KIPARAMETERS_H

#include "parameterfile.h"
#include "src/external/bitmanipulation.h"
#include "src/external/debug.h"

/**
 * Object for the ki parameter section of a .pak file.
 */
class KiParameters :  ParameterFile
{
public:
    typedef enum
    {
        Header,
        Damage,
        DamageGuarding,
        KiCost,
        Speed,
        Spread,
        Range,
        Knockback,
        Unk20,
        Hitstun,
        Unk25,
        Unk26,
        Unk27,
        Size,
        Trail,
        Unk30,
        Color,
        Amount,
        Trajectory,
        Footer,
        KiParameterCount
    } KiParameter;

    Param_Offset parameter[KiParameterCount];

    KiParameters(QByteArray ParameterData, Options* options);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QSpinBox* Object);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QComboBox* Object);
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    unsigned short GetUShortParameter(QSpinBox* Object);

    int GetIntParameter(QSpinBox* Object);
    float GetFloatParameter(QDoubleSpinBox* Object);
    void SetUByteParameter(QSpinBox* Object, unsigned char NewValue);
    void SetUByteParameter(QComboBox* Object, unsigned char NewValue);
    void SetUShortParameter(QSpinBox* Object, unsigned short NewValue);
    void SetIntParameter(QSpinBox* Object, int NewValue);
    void SetFloatParameter(QDoubleSpinBox* Object, float NewValue);

    void setCurrentBlast(int BlastID);
    /**
     * Gets the parameter type of this parameter object.
     */
    ParameterType GetParameterType()
    { return KI_BLAST; };
    QByteArray GetFileData();
    void SetFileData(QByteArray NewData);
    Options* options = nullptr;
private:
    const char* rawData = nullptr;
    unsigned short blastOffset;
};

#endif // KIPARAMETERS_H
