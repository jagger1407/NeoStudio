#ifndef GENERALPARAMETERS_H
#define GENERALPARAMETERS_H

#include "src/external/debug.h"
#include "src/bitmanipulation.h"
#include "src/neo_info.h"

/**
 * Object for the general parameter section of a .pak file.
 */
class GeneralParameters
{
public:
    typedef enum
    {
        Transform,
        TransformCost = Transform + 4,
        Unk_0x8 = TransformCost + 4,
        Unk_0x9,
        FusionCost,
        FusionType = FusionCost + 3,
        FusionCharID = FusionType + 3,
        FusionPartnerID = FusionCharID + 3,
        FusionTeamID = FusionPartnerID + 3,
        Unk_0x28 = FusionTeamID + 18,
        ZSearch,
        Unk_0x2F = ZSearch + 6,
        FlagGroup,
        GreatApeMode = FlagGroup + 3,
        Unk_0x3E,
        AuraColor,
        Collision,
        KiBlastAmount = Collision + 3,
        RushingTechnique,
        CounterMove = RushingTechnique + 4,
        StepInMove = CounterMove + 3,
        ChargedBlastAmount = StepInMove + 3,
        Unk_0x58,
        Unk_0x5C,
        Unk_0x60,
        Unk_0x64,
        Unk_0x68,
        BlastStockAmount,
        KiChargeSpeed,
        KiChargeSpeedWater,
        BaseKiRegen,
        CounterKi,
        Unk_0x80,
        PowerGuardKiCost,
        Unk_0x88,
        BlastGaugeSpeed,
        BlueKiChargeSpeed,
        MaxPowerModeDuration,
        Gravity,
        Unk_0x9C,
        Unk_0xA0,
        Unk_0xA4,
        MaxDragonSmashes,
        MaxVanishingAttacks,
        Unk_0xAA,
        MeleeChargeSpeed,
        Unk_0xB0,
        DamageMultiplier,
        SwitchRegenSpeed,
        Unk_0xBC,
        Unk_0xBF = Unk_0xBC + 3,
        Unk_0xC2 = Unk_0xBF + 3,
        Unk_0xC5 = Unk_0xC2 + 3,
        Unk_0xCF = Unk_0xC5 + 3,
        GeneralParameterCount = Unk_0xCF + 3
    } GeneralParameter;
    /**
    *  Offsets for each general parameter, in order of appearance.
    */
    Param_Offset parameter[GeneralParameterCount];
    /**
     * Constructs new General Parameter Object.
     */
    GeneralParameters(QByteArray ParameterData);
    bool GetFlagParameter(QCheckBox* Object);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QObject* Object);
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    unsigned short GetUShortParameter(QSpinBox* Object);

    int GetIntParameter(QSpinBox* Object);
    float GetFloatParameter(QDoubleSpinBox* Object);
    void SetFlagParameter(QCheckBox* Object, bool NewValue);
    void SetUByteParameter(QObject* Object, unsigned char NewValue);
    void SetUShortParameter(QSpinBox* Object, unsigned short NewValue);
    void SetIntParameter(QSpinBox* Object, int NewValue);
    void SetFloatParameter(QDoubleSpinBox* Object, float NewValue);
    QByteArray* GetParameterData();
    void SetParameterData(QByteArray NewData);
    /**
     * The parameter type of this parameter object.
     */
    const ParameterType paramType = PARAM_TYPE_GENERAL;
private:
    const char* constData = nullptr;
    QByteArray paramData;
};

#endif // GENERALPARAMETERS_H
