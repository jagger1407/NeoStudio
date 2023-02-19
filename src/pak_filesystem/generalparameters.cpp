#include "generalparameters.h"

GeneralParameters::GeneralParameters(QByteArray ParameterData, Options* options) : options(options)
{
    fileData = ParameterData;
    constData = fileData.constData();
    if(fileData == nullptr || constData == nullptr)
    {
        Debug::Log("Construction of GeneralParameter object failed!", Debug::ERROR, options);
        return;
    }

#if 1 // Defining all known parameter offsets
    for(int i=0;i<4;i++)
    {
        parameter[Transform+i].offset = 0x00 + i;
        parameter[TransformCost+i].offset = 0x04 + i;
        parameter[RushingTechnique+i].offset = 0x4D + i;
    }
    for(int i=0;i<3;i++)
    {
        parameter[FusionCost+i].offset = 0x0A + i;
        parameter[FusionType+i].offset = 0x0D + i;
        parameter[FusionCharID+i].offset = 0x10 + i;
        parameter[FusionPartnerID+i].offset = 0x13 + i;
        parameter[Collision+i].offset = 0x40 + (4 * i);
        parameter[CounterMove+i].offset = 0x51 + i;
    }
    for(int i=0;i<18;i++) parameter[FusionTeamID+i].offset = 0x16 + i;
    parameter[ZSearch].offset = 0x29;
    parameter[FlagByte].offset = 0x30;
    parameter[FlagByte+1].offset = 0x31;
    parameter[FlagByte+2].offset = 0x34;
    parameter[FlagByte+3].offset = 0x35;
    parameter[FlagByte+4].offset = 0x36;
    parameter[FlagByte+5].offset = 0x37;
    parameter[FlagByte+6].offset = 0x38;
    parameter[FlagByte+7].offset = 0x39;
    parameter[FlagByte+8].offset = 0x3E;
    parameter[AuraColor].offset = 0x3F;
    parameter[KiBlastAmount].offset = 0x4C;
    parameter[StepInMove].offset = 0x54;
    parameter[ChargedBlastAmount].offset = 0x57;
    parameter[BlastStockAmount].offset = 0x6C;
    parameter[KiChargeSpeed].offset = 0x70;
    parameter[KiChargeSpeedWater].offset = 0x74;
    parameter[BaseKiRegen].offset = 0x78;
    parameter[CounterKi].offset = 0x7C;
    parameter[BlastGaugeSpeed].offset = 0x8C;
    parameter[MaxKiChargeSpeed].offset = 0x90;
    parameter[MaxPowerModeDuration].offset = 0x94;
    parameter[Gravity].offset = 0x98;
    parameter[MaxDragonSmashes].offset = 0xA8;
    parameter[MaxVanishingAttacks].offset = 0xA9;
    parameter[MeleeChargeSpeed].offset = 0xAC;
    parameter[DamageMultiplier].offset = 0xB4;
    parameter[SwitchRegenSpeed].offset = 0xB8;
#endif

    Debug::Log("New GeneralParameter object constructed.", Debug::INFO, options);
}

/**Gets file data of this parameter file as a whole QByteArray.*/
QByteArray GeneralParameters::GetFileData()
{
    Debug::Log("GetFileData called.", Debug::INFO, options);
    return QByteArray(fileData);
}
/**Sets the entire parameter file data array at once to NewData, this should normally not be used.*/
void GeneralParameters::SetFileData(QByteArray NewData)
{
    Debug::Log("SetFileData called.", Debug::INFO, options);
    fileData.replace(0, fileData.size(), NewData);
}

bool GeneralParameters::GetFlagParameter(QCheckBox* Object)
{
    Debug::Log("GetFlagParameter called.", Debug::INFO, options);
    QObject* byte = Object->parent();
    int bit = Object->objectName().right(1).toUInt() - 1;
    for(int i=FlagByte;i<FlagByte + 9;i++)
    {
        if((long)byte == (long)parameter[i].UiElement) return BitManipulation::Bit(*(constData + parameter[i].offset), bit);
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return false;
}
unsigned char GeneralParameters::GetUByteParameter(QSpinBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<GeneralParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(constData + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return (unsigned char)-1;
}
unsigned char GeneralParameters::GetUByteParameter(QComboBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    if(Object == (void*)parameter[ZSearch].UiElement) return *(constData + parameter[ZSearch].offset);
    else if(Object == (void*)parameter[ZSearch].UiElement) return *(constData + parameter[AuraColor].offset);
    else if(Object == (void*)parameter[StepInMove].UiElement) return *(constData + parameter[StepInMove].offset);
    else if(Object == (void*)parameter[AuraColor].UiElement) return *(constData + parameter[AuraColor].offset);
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return (unsigned char)-1;
}
unsigned char GeneralParameters::GetUByteParameter(QPushButton* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    for(int i=FusionType;i<=CounterMove+2;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(constData + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return (unsigned char)-1;
}
unsigned short GeneralParameters::GetUShortParameter(QSpinBox* Object)
{
    Debug::Log("GetUShortParameter called.", Debug::INFO, options);
    // There are no 2-Byte Parameters in this Parameter-section.
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING, options);
    return (unsigned short)-1;
}
int GeneralParameters::GetIntParameter(QSpinBox* Object)
{
    Debug::Log("GetIntParameter called.", Debug::INFO, options);
    for(int i=KiChargeSpeed;i<=BlastGaugeSpeed;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(int*)(constData + parameter[i].offset);
    }

    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return -1;
}
float GeneralParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO, options);
    for(int i=0;i<=GeneralParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(float*)(constData + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return -1;
}

void GeneralParameters::SetFlagParameter(QCheckBox* Object, bool NewValue)
{
    Debug::Log("SetFlagParameter called.", Debug::INFO, options);
    QObject* byte = Object->parent();
    int bit = Object->objectName().right(1).toUInt();
    for(int i=0;i<9;i++)
    {
        if((long)byte == (long)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset, bit, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
}

void GeneralParameters::SetUByteParameter(QSpinBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<GeneralParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
}
void GeneralParameters::SetUByteParameter(QComboBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    if(Object == (void*)parameter[ZSearch].UiElement)
    {
        ChangeData(parameter[ZSearch].offset, NewValue);
        return;
    }
    else if(Object == (void*)parameter[ZSearch].UiElement)
    {
        ChangeData(parameter[AuraColor].offset, NewValue);
        return;
    }
    else if(Object == (void*)parameter[StepInMove].UiElement)
    {
        ChangeData(parameter[StepInMove].offset, NewValue);
        return;
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return;
}
void GeneralParameters::SetUByteParameter(QPushButton* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    for(int i=FusionType;i<=CounterMove+2;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return;
}
void GeneralParameters::SetUShortParameter(QSpinBox* Object, unsigned short NewValue)
{
    Debug::Log("SetUShortParameter called.", Debug::INFO, options);
    // There are no 2-Byte Parameters in this Parameter-section.
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING, options);
}
void GeneralParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    Debug::Log("SetIntParameter called.", Debug::INFO, options);
    for(int i=KiChargeSpeed;i<=BlastGaugeSpeed;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset, NewValue);
            return;
        }
    }

    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return;
}
void GeneralParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO, options);
    for(int i=0;i<=GeneralParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return;
}
