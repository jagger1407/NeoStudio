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
        MaxKiChargeSpeed,
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
     * Constructs new General Parameter Object.
     */
    GeneralParameters(QByteArray ParameterData);
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
    /**
     * Gets the parameter type of this parameter object.
     */
    ParameterType GetParameterType()
    { return GENERAL; };
    QByteArray GetFileData();
    void SetFileData(QByteArray NewData);
    QObject* UiElements[GeneralParameterCount];
private:
    const char* constData = nullptr;
    /**
    *  Offsets for each general parameter, in order of appearance.
    */
    param_offset offset[GeneralParameterCount] =
    {
    /*transformation*/          0x00, 0x01, 0x02, 0x03 ,
    /*transformationCost*/      0x04, 0x05, 0x06, 0x07 ,
    /*fusionCost*/              0x0A, 0x0B, 0x0C ,
    /*fusionType*/              0x0D, 0x0E, 0x0F ,
    /*fusionCharID*/            0x10, 0x11, 0x12 ,
    /*fusionPartnerID*/         0x13, 0x14, 0x15 ,
    /*fusionTeamID*/            0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,
                                0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21,
                                0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    /*zSearchType*/             0x29,
    /*flagByte*/                0x30, 0x31, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3E,
    /*auraColor*/               0x3F,
    /*collision*/               0x40, 0x44, 0x48,
    /*kiBlastAmount*/           0x4C,
    /*rushingTechnique*/        0x4D, 0x4E, 0x4F, 0x50 ,
    /*counter*/                 0x51, 0x52, 0x53 ,
    /*stepInMove*/              0x54,
    /*kiBlastAmountCharged*/    0x57,
    /*blastStockAmount*/        0x6C,
    /*kiChargeSpeed*/           0x70,
    /*kiChargeSpeedWater*/      0x74,
    /*baseKiRegen*/             0x78,
    /*counterKiConsumption*/    0x7C,
    /*blastGaugeSpeed*/         0x8C,
    /*maxKiChargingSpeed*/      0x90, // uncertain what this is
    /*maxPowerModeDuration*/    0x94,
    /*gravity*/                 0x98,
    /*maxPowerDragonSmashes*/   0xA8,
    /*maxPowerVanishingAttacks*/0xA9,
    /*meleeChargeSpeed*/        0xAC,
    /*damageMultiplier*/        0xB4,
    /*switchRegenSpeed*/        0xB8,
    };
};

#endif // GENERALPARAMETERS_H
