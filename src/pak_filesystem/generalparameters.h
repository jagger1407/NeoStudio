#ifndef GENERALPARAMETERS_H
#define GENERALPARAMETERS_H

#include "parameterfile.h"
#include "src/external/bitmanipulation.h"
#include "src/external/debug.h"

/**
 * Object for the general parameter section of a .pak file.
 */
class GeneralParameters :  ParameterFile
{
public:
    typedef enum
    {
        Transform,
        TransformCost = 4,
        FusionCost = 8,
        FusionType = 11,
        FusionCharID = 14,
        FusionPartnerID = 17,
        FusionTeamID = 20,
        ZSearch = 38,
        FlagByte,
        AuraColor = 48,
        Collision,
        KiBlastAmount = 52,
        RushingTechnique,
        CounterMove = 57,
        StepInMove = 60,
        ChargedBlastAmount,
        BlastStockAmount,
        KiChargeSpeed,
        KiChargeSpeedWater,
        BaseKiRegen,
        CounterKi,
        BlastGaugeSpeed,
        BlueKiChargeSpeed,
        MaxPowerModeDuration,
        Gravity,
        MaxDragonSmashes,
        MaxVanishingAttacks,
        MeleeChargeSpeed,
        DamageMultiplier,
        SwitchRegenSpeed,
        GeneralParameterCount
    } GeneralParameter;
    /**
    *  Offsets for each general parameter, in order of appearance.
    */
    Param_Offset parameter[GeneralParameterCount];
    /**
     * Constructs new General Parameter Object.
     */
    GeneralParameters(QByteArray ParameterData, Options* options);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QSpinBox* Object);
    unsigned char GetUByteParameter(QComboBox* Object);
    unsigned char GetUByteParameter(QPushButton* Object);
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    unsigned short GetUShortParameter(QSpinBox* Object);

    int GetIntParameter(QSpinBox* Object);
    float GetFloatParameter(QDoubleSpinBox* Object);
    bool GetFlagParameter(QCheckBox* Object);
    void SetUByteParameter(QSpinBox* Object, unsigned char NewValue);
    void SetUByteParameter(QComboBox* Object, unsigned char NewValue);
    void SetUByteParameter(QPushButton* Object, unsigned char NewValue);
    void SetUShortParameter(QSpinBox* Object, unsigned short NewValue);
    void SetIntParameter(QSpinBox* Object, int NewValue);
    void SetFloatParameter(QDoubleSpinBox* Object, float NewValue);
    void SetFlagParameter(QCheckBox* Object, bool NewValue);
    QByteArray GetFileData();
    void SetFileData(QByteArray NewData);
    /**
     * Gets the parameter type of this parameter object.
     */
    ParameterType GetParameterType()
    { return PARAM_TYPE_GENERAL; };
    Options* options = nullptr;
private:
    const char* constData = nullptr;
};

#endif // GENERALPARAMETERS_H
