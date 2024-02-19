#ifndef KIPARAMETERS_H
#define KIPARAMETERS_H

#include "src/neo_info.h"
#include "src/external/debug.h"
#include "src/bitmanipulation.h"

/**
 * Object for the ki parameter section of a .pak file.
 */
class KiParameters
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

    KiParameters(QByteArray ParameterData);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QObject* Object);
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    unsigned short GetUShortParameter(QSpinBox* Object);

    bool GetFlagParameter(QCheckBox* Object);
    int GetIntParameter(QSpinBox* Object);
    float GetFloatParameter(QDoubleSpinBox* Object);
    void SetFlagParameter(QCheckBox* Object, int NewState);
    void SetUByteParameter(QObject* Object, unsigned char NewValue);
    void SetUShortParameter(QSpinBox* Object, unsigned short NewValue);
    void SetIntParameter(QSpinBox* Object, int NewValue);
    void SetFloatParameter(QDoubleSpinBox* Object, float NewValue);

    void setCurrentBlast(int BlastID);
    /**
     * The parameter type of this parameter object.
     */
    const ParameterType paramType = PARAM_TYPE_KI_BLAST;
    QByteArray* GetParameterData();
    void SetParameterData(QByteArray NewData);
private:
    const char* constData = nullptr;
    QByteArray paramData;
    unsigned short blastOffset;
};

#endif // KIPARAMETERS_H
