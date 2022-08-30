#ifndef GENERALPARAMETERS_H
#define GENERALPARAMETERS_H

#include "parameterfile.h"
#include "src/external/bitmanipulation.h"
#include "src/external/debug.h"

#define param_offset const unsigned char

/**
 * Object for the general parameter section of a .pak file.
 */
class GeneralParameters :  ParameterFile
{
public:
    /**
     * Constructs new General Parameter Object.
     */
    GeneralParameters(QByteArray ParameterData);
    /**Gets the single Byte parameter value of the parameter corresponding to the Object.*/
    unsigned char GetUByteParameter(QString ObjectName);
    /**Gets the 2-Byte parameter value of the parameter corresponding to the Object.*/
    unsigned short GetUShortParameter(QString ObjectName);

    int GetIntParameter(QString ObjectName);
    float GetFloatParameter(QString ObjectName);
    bool GetFlagParameter(QString ObjectName);
    void SetUByteParameter(QString ObjectName, unsigned char NewValue);
    void SetUShortParameter(QString ObjectName, unsigned short NewValue);
    void SetIntParameter(QString ObjectName, int NewValue);
    void SetFloatParameter(QString ObjectName, float NewValue);
    void SetFlagParameter(QString ObjectName, bool NewValue);

    const char* constData = nullptr;
    /**
     * Gets the parameter type of this parameter object.
     */
    ParameterType GetParameterType()
    { return GENERAL; };
    QByteArray GetFileData();
    void SetFileData(QByteArray NewData);
private:
    char* editableData = nullptr;
    // Offsets for each parameter,
    // in order of appearance in the actual file.
    param_offset transformation[4] = { 0x00, 0x01, 0x02, 0x03 };
    param_offset transformationCost[4] = { 0x04, 0x05, 0x06, 0x07 };
    param_offset fusionCost[3] = { 0x0A, 0x0B, 0x0C };
    param_offset fusionType[3] = { 0x0D, 0x0E, 0x0F };
    param_offset fusionCharID[3] = { 0x10, 0x11, 0x12 };
    param_offset fusionPartnerID[3] = { 0x13, 0x14, 0x15 };
    param_offset fusionTeamID[3][6] = { { 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B },
                                        { 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21 },
                                        { 0x22, 0x23, 0x24, 0x25, 0x26, 0x27 } };
    param_offset zSearchType = 0x29;
    param_offset flagByte[9] = { 0x30, 0x31, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3E };
    param_offset auraColor = 0x3F;
    param_offset collision[3] = { 0x40, 0x44, 0x48};
    param_offset kiBlastAmount = 0x4C;
    param_offset rushingTechnique[4] = { 0x4D, 0x4E, 0x4F, 0x50 };
    param_offset counter[3] = { 0x51, 0x52, 0x53 };
    param_offset stepInMove = 0x54;
    param_offset kiBlastAmountCharged = 0x57;
    param_offset blastStockAmount = 0x6C;
    param_offset kiChargeSpeed = 0x70;
    param_offset kiChargeSpeedWater = 0x74;
    param_offset baseKiRegen = 0x78;
    param_offset counterKiConsumption = 0x7C;
    param_offset blastGaugeSpeed = 0x8C;
    param_offset maxKiChargingSpeed = 0x90; // uncertain what this is
    param_offset maxPowerModeDuration = 0x94;
    param_offset gravity = 0x98;
    param_offset maxPowerDragonSmashes = 0xA8;
    param_offset maxPowerVanishingAttacks = 0xA9;
    param_offset meleeChargeSpeed = 0xAC;
    param_offset damageMultiplier = 0xB4;
    param_offset switchRegenSpeed = 0xB8;
};

#endif // GENERALPARAMETERS_H
