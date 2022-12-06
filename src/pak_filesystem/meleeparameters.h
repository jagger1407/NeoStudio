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

    MeleeParameters(QByteArray ParameterData);
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
    { return MELEE; };
    QByteArray GetFileData();
    void SetFileData(QByteArray NewData);
    QObject* UiElements[MeleeParameterCount];
private:
    const char* rawData = nullptr;
    unsigned short attackOffset;
    param_offset offset[MeleeParameterCount] = {
        /*Header*/          0x00,
        /*SecondaryString*/ 0x01,
        /*LockOnLoss*/      0x01,
        /*Damage*/          0x04,
        /*DamageGuarding*/  0x08,
        /*KiLoss*/          0x0C,
        /*KiGain*/          0x10,
        /*Unknown*/         0x14, 0x18, 0x1C,
        /*Hitstun*/         0x20,
        /*Unknown*/         0x21,0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
        /*VFX*/             0x28,
        /*SFX*/             0x29,
        /*Unknown*/         0x2A, 0x2B,
        /*Knockback*/       0x2C,
        /*Unknown*/         0x30,
        /*Reach*/           0x34,
        /*Unknown*/         0x38, 0x3C, 0x40, 0x44, 0x48,0x4C, 0x50, 0x54, 0x58, 0x5C,
        /*EffectGuard*/     0x60,
        /*EffectCounter*/   0x61,
        /*GuardType*/       0x62,
        /*Unknown*/         0x63 };
};

#endif // MELEEPARAMETERS_H
