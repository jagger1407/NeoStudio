#ifndef MELEEPARAMETERS_H
#define MELEEPARAMETERS_H

#include "parameterfile.h"
#include "src/external/bitmanipulation.h"
#include "src/external/debug.h"

/**
 * Object for the melee parameter section of a .pak file.
 */
class MeleeParameters :  ParameterFile
{
public:
    typedef enum
    {
        Header,
        SecondaryString,
        LockOnLoss,
        Damage,
        DamageGuarding,
        KiLoss,
        KiGain,
        Unk14,
        Unk18,
        Unk1C,
        Hitstun,
        Unk21,
        Unk22,
        Unk23,
        Unk24,
        Unk25,
        Unk26,
        Unk27,
        VFX,
        SFX,
        Unk2A,
        Unk2B,
        Knockback,
        Unk30,
        Reach,
        Unk38,
        Unk3C,
        Unk40,
        Unk44,
        Unk48,
        Unk4C,
        Unk50,
        Unk54,
        Unk58,
        Unk5C,
        EffectGuard,
        EffectCounter,
        GuardType,
        Unk63,
        MeleeParameterCount
    } MeleeParameter;

    Param_Offset parameter[MeleeParameterCount];

    MeleeParameters(QByteArray ParameterData, Options* options);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QSpinBox* Object);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QComboBox* Object);
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    unsigned short GetUShortParameter(QSpinBox* Object);

    int GetIntParameter(QSpinBox* Object);
    float GetFloatParameter(QDoubleSpinBox* Object);
    bool GetFlagParameter(QCheckBox* Object);
    void SetUByteParameter(QSpinBox* Object, unsigned char NewValue);
    void SetUByteParameter(QComboBox* Object, unsigned char NewValue);
    void SetUShortParameter(QSpinBox* Object, unsigned short NewValue);
    void SetIntParameter(QSpinBox* Object, int NewValue);
    void SetFloatParameter(QDoubleSpinBox* Object, float NewValue);
    void SetFlagParameter(QCheckBox* Object, bool NewValue);

    void setCurrentAttack(int AttackID);
    /**
     * Gets the parameter type of this parameter object.
     */
    ParameterType GetParameterType()
    { return PARAM_TYPE_MELEE; };
    QByteArray GetFileData();
    void SetFileData(QByteArray NewData);
    Options* options = nullptr;
private:
    const char* rawData = nullptr;
    unsigned short attackOffset;
};

#endif // MELEEPARAMETERS_H
