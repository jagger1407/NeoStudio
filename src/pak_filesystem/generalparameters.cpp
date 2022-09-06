#include "generalparameters.h"

GeneralParameters::GeneralParameters(QByteArray ParameterData)
{
    fileData = ParameterData;
    constData = fileData.constData();
    editableData = fileData.data();
    if(fileData == nullptr || constData == nullptr || editableData == nullptr)
    {
        Debug::Log("Construction of GeneralParameter object failed!", Debug::ERROR);
        return;
    }
    Debug::Log("New GeneralParameter object constructed.", Debug::INFO);
}
unsigned char GeneralParameters::GetUByteParameter(QString ObjectName)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO);
    QStringList objName = ObjectName.split('_');
    unsigned char objNum[2];
    if(objName.count() > 1) objNum[0] = objName[1].toUShort();
    if(objName.count() > 2) objNum[1] = objName[2].toUShort();
    if(objName[0] == "TransformIDBox") return *(constData + transformation[objNum[0] - 1]);
    else if(objName[0] == "TransformCostBox") return *(constData + transformationCost[objNum[0] - 1]);
    else if(objName[0] == "FusionCostBox") return *(constData + fusionCost[objNum[0] - 1]);
    else if(objName[0] == "FusionTypeBtn") return *(constData + fusionType[objNum[0] - 1]);
    else if(objName[0] == "FusionIDBox") return *(constData + fusionCharID[objNum[0] - 1]);
    else if(objName[0] == "PartnerIDBox") return *(constData + fusionPartnerID[objNum[0] - 1]);
    else if(objName[0] == "PartnerTeamIDBox") return *(constData + fusionTeamID[objNum[0] - 1][objNum[1] - 1]);
    else if(objName[0] == "ZSearchBox") return *(constData + zSearchType);
    else if(objName[0] == "AuraColorBox") return *(constData + auraColor);
    else if(objName[0] == "RushTechBtn") return *(constData + rushingTechnique[objNum[0] - 1]);
    else if(objName[0] == "CounterBtn") return *(constData + counter[objNum[0] - 1]);
    else if(objName[0] == "KiBlastBox") return *(constData + kiBlastAmount);
    else if(objName[0] == "BlastStockBox") return *(constData + blastStockAmount);
    else if(objName[0] == "StepInBox") return *(constData + stepInMove);
    else if(objName[0] == "KiBlastChargedBox") return *(constData + kiBlastAmountCharged);
    else if(objName[0] == "DragonHomingBox") return *(constData + maxPowerDragonSmashes);
    else if(objName[0] == "VanishingAttackBox") return *(constData + maxPowerVanishingAttacks);
    else
    {
        Debug::Log("Object '" + ObjectName + "' not input field.", Debug::WARNING);
        return -1;
    }
}
unsigned short GeneralParameters::GetUShortParameter(QString ObjectName)
{
    Debug::Log("GetUShortParameter called.", Debug::INFO);
    // There are no 2-Byte Parameters in this Parameter-section.
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
    return 0;
}
int GeneralParameters::GetIntParameter(QString ObjectName)
{
    Debug::Log("GetIntParameter called.", Debug::INFO);
    if(ObjectName == "KiChargeBox") return *(int*)(constData + kiChargeSpeed);
    else if(ObjectName == "KiChargeWaterBox") return *(int*)(constData + kiChargeSpeedWater);
    else if(ObjectName == "BaseKiRegenBox") return *(int*)(constData + baseKiRegen);
    else if(ObjectName == "CounterKiBox") return *(int*)(constData + counterKiConsumption);
    else if(ObjectName == "BlastGaugeBox") return *(int*)(constData + blastGaugeSpeed);
    else
    {
        Debug::Log("Object '" + ObjectName + "' not input field.", Debug::WARNING);
        return -1;
    }
}
float GeneralParameters::GetFloatParameter(QString ObjectName)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO);
    if(ObjectName == "MaxPowDurBox") return *(float*)(constData + maxPowerModeDuration);
    else if(ObjectName == "GravityBox") return *(float*)(constData + gravity);
    else if(ObjectName.contains("CollisionSpinBox")) return *(float*)(constData + collision[ObjectName.right(1).toUShort() - 1]);
    else if(ObjectName == "DmgMulBox") return *(float*)(constData + damageMultiplier);
    else if(ObjectName == "TeamGaugeBox") return *(float*)(constData + switchRegenSpeed);
    else if(ObjectName == "ChargeBarSpdBox") return *(float*)(constData + meleeChargeSpeed);
    else
    {
        Debug::Log("Object '" + ObjectName + "' not input field.", Debug::WARNING);
        return -1;
    }
}
bool GeneralParameters::GetFlagParameter(QString ObjectName)
{
    Debug::Log("GetFlagParameter called.", Debug::INFO);
    QStringList objName = ObjectName.split('_');
    return BitManipulation::Bit(*(constData + flagByte[objName[1].toUShort() - 1]), objName[2].toUShort() - 1);
}
void GeneralParameters::SetUByteParameter(QString ObjectName, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO);
    QStringList objName = ObjectName.split('_');
    unsigned char objNum[2];
    if(objName.count() > 1) objNum[0] = objName[1].toUShort();
    if(objName.count() > 2) objNum[1] = objName[2].toUShort();
    if(objName[0] == "TransformIDBox") ChangeData(transformation[objNum[0] - 1], NewValue);
    else if(objName[0] == "TransformCostBox") ChangeData(transformationCost[objNum[0] - 1], NewValue);
    else if(objName[0] == "FusionCostBox") ChangeData(fusionCost[objNum[0] - 1], NewValue);
    else if(objName[0] == "FusionTypeBtn") ChangeData(fusionType[objNum[0] - 1], NewValue);
    else if(objName[0] == "FusionIDBox") ChangeData(fusionCharID[objNum[0] - 1], NewValue);
    else if(objName[0] == "PartnerIDBox") ChangeData(fusionPartnerID[objNum[0] - 1], NewValue);
    else if(objName[0] == "PartnerTeamIDBox") ChangeData(fusionTeamID[objNum[0] - 1][objNum[1] - 1], NewValue);
    else if(objName[0] == "ZSearchBox") ChangeData(zSearchType, NewValue);
    else if(objName[0] == "AuraColorBox") ChangeData(auraColor, NewValue);
    else if(objName[0] == "RushTechBtn") ChangeData(rushingTechnique[objNum[0] - 1], NewValue);
    else if(objName[0] == "CounterBtn") ChangeData(counter[objNum[0] - 1], NewValue);
    else if(objName[0] == "KiBlastBox") ChangeData(kiBlastAmount, NewValue);
    else if(objName[0] == "BlastStockBox") ChangeData(blastStockAmount, NewValue);
    else if(objName[0] == "StepInBox") ChangeData(stepInMove, NewValue);
    else if(objName[0] == "KiBlastChargedBox") ChangeData(kiBlastAmountCharged, NewValue);
    else if(objName[0] == "DragonHomingBox") ChangeData(maxPowerDragonSmashes, NewValue);
    else if(objName[0] == "VanishingAttackBox") ChangeData(maxPowerVanishingAttacks, NewValue);
    else
    {
        Debug::Log("Object '" + ObjectName + "' not input field.", Debug::WARNING);
        return;
    }
}
void GeneralParameters::SetUShortParameter(QString ObjectName, unsigned short NewValue)
{
    Debug::Log("SetUShortParameter called.", Debug::INFO);
    // There are no 2-Byte Parameters in this Parameter-section.
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
}
void GeneralParameters::SetIntParameter(QString ObjectName, int NewValue)
{
    Debug::Log("SetIntParameter called.", Debug::INFO);
    if(ObjectName == "KiChargeBox") ChangeData(kiChargeSpeed, NewValue);
    else if(ObjectName == "KiChargeWaterBox") ChangeData(kiChargeSpeedWater, NewValue);
    else if(ObjectName == "BaseKiRegenBox") ChangeData(baseKiRegen, NewValue);
    else if(ObjectName == "CounterKiBox") ChangeData(counterKiConsumption, NewValue);
    else if(ObjectName == "BlastGaugeBox") ChangeData(blastGaugeSpeed, NewValue);
    else
    {
        Debug::Log("Object '" + ObjectName + "' not input field.", Debug::WARNING);
        return;
    }
}
void GeneralParameters::SetFloatParameter(QString ObjectName, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO);
    QStringList objName = ObjectName.split('_');
    if(ObjectName == "MaxPowDurBox") ChangeData(maxPowerModeDuration, NewValue);
    else if(ObjectName == "GravityBox") ChangeData(gravity, NewValue);
    else if(ObjectName.contains("CollisionSpinBox")) ChangeData(collision[ObjectName.right(1).toUShort() - 1], NewValue);
    else if(ObjectName == "DmgMulBox") ChangeData(damageMultiplier, NewValue);
    else if(ObjectName == "TeamGaugeBox") ChangeData(switchRegenSpeed, NewValue);
    else if(ObjectName == "ChargeBarSpdBox") ChangeData(meleeChargeSpeed, NewValue);
    else
    {
        Debug::Log("Object '" + ObjectName + "' not input field.", Debug::WARNING);
        return;
    }
}
void GeneralParameters::SetFlagParameter(QString ObjectName, bool NewValue)
{
    QStringList objName = ObjectName.split('_');
    BitManipulation::SetBit(fileData.data() + flagByte[objName[1].toUShort()-1], objName[2].toUShort()-1, NewValue);
}
QByteArray GeneralParameters::GetFileData()
{
    return QByteArray(fileData);
}
void GeneralParameters::SetFileData(QByteArray NewData)
{
    fileData.replace(0, fileData.size(), NewData);
}
