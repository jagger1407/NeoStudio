#include "generalparameters.h"

GeneralParameters::GeneralParameters(QByteArray ParameterData, Options* options) : options(options)
{
    fileData = ParameterData;
    constData = fileData.constData();
    if(fileData == nullptr || constData == nullptr)
    {
        Debug::Log("Construction of GeneralParameter object failed! No data passed.", Debug::ERROR, options);
        return;
    }

#if 1 // Defining all known parameter offsets
    parameter[Transform].offset = 0x00;
    parameter[Transform + 1].offset = 0x01;
    parameter[Transform + 2].offset = 0x02;
    parameter[Transform + 3].offset = 0x03;
    parameter[TransformCost].offset = 0x04;
    parameter[TransformCost + 1].offset = 0x05;
    parameter[TransformCost + 2].offset = 0x06;
    parameter[TransformCost + 3].offset = 0x07;
    parameter[Unk_0x8].offset = 0x08;
    parameter[Unk_0x9].offset = 0x09;
    parameter[FusionCost].offset = 0x0A;
    parameter[FusionCost + 1].offset = 0x0B;
    parameter[FusionCost + 2].offset = 0x0C;
    parameter[FusionType].offset = 0x0D;
    parameter[FusionType + 1].offset = 0x0E;
    parameter[FusionType + 2].offset = 0x0F;
    parameter[FusionCharID].offset = 0x10;
    parameter[FusionCharID + 1].offset = 0x11;
    parameter[FusionCharID + 2].offset = 0x12;
    parameter[FusionPartnerID].offset = 0x13;
    parameter[FusionPartnerID + 1].offset = 0x14;
    parameter[FusionPartnerID + 2].offset = 0x15;
    for(int i=0;i<6;i++)
    {
        parameter[FusionTeamID + i].offset = 0x16 + i;
        parameter[FusionTeamID + 6 + i].offset = 0x1C + i;
        parameter[FusionTeamID + 12 + i].offset = 0x22 + i;

        parameter[ZSearch + i].offset = 0x29 + i;
    }

    parameter[Unk_0x28].offset = 0x28;
    parameter[Unk_0x2F].offset = 0x2F;
    parameter[FlagGroup].offset = 0x30;
    parameter[FlagGroup + 1].offset = 0x34;
    parameter[FlagGroup + 2].offset = 0x38;
    parameter[GreatApeMode].offset = 0x3E;
    parameter[Unk_0x3E].offset = 0x3E;
    parameter[AuraColor].offset = 0x3F;
    parameter[Collision].offset = 0x40;
    parameter[Collision + 1].offset = 0x44;
    parameter[Collision + 2].offset = 0x48;
    parameter[KiBlastAmount].offset = 0x4C;
    parameter[RushingTechnique].offset = 0x4D;
    parameter[RushingTechnique + 1].offset = 0x4E;
    parameter[RushingTechnique + 2].offset = 0x4F;
    parameter[RushingTechnique + 3].offset = 0x50;
    parameter[CounterMove].offset = 0x51;
    parameter[CounterMove + 1].offset = 0x52;
    parameter[CounterMove + 2].offset = 0x53;
    parameter[StepInMove].offset = 0x54;
    parameter[StepInMove + 1].offset = 0x55;
    parameter[StepInMove + 2].offset = 0x56;
    parameter[ChargedBlastAmount].offset = 0x57;
    parameter[Unk_0x58].offset = 0x58;
    parameter[Unk_0x5C].offset = 0x5C;
    parameter[Unk_0x60].offset = 0x60;
    parameter[Unk_0x64].offset = 0x64;
    parameter[Unk_0x68].offset = 0x68;
    parameter[BlastStockAmount].offset = 0x6C;
    parameter[KiChargeSpeed].offset = 0x70;
    parameter[KiChargeSpeedWater].offset = 0x74;
    parameter[BaseKiRegen].offset = 0x78;
    parameter[CounterKi].offset = 0x7C;
    parameter[Unk_0x80].offset = 0x80;
    parameter[Unk_0x84].offset = 0x84;
    parameter[Unk_0x88].offset = 0x88;
    parameter[BlastGaugeSpeed].offset = 0x8C;
    parameter[BlueKiChargeSpeed].offset = 0x90;
    parameter[MaxPowerModeDuration].offset = 0x94;
    parameter[Gravity].offset = 0x98;
    parameter[Unk_0x9C].offset = 0x9C;
    parameter[Unk_0xA0].offset = 0xA0;
    parameter[MaxDragonSmashes].offset = 0xA8;
    parameter[MaxVanishingAttacks].offset = 0xA9;
    parameter[Unk_0xAA].offset = 0xAA;
    parameter[MeleeChargeSpeed].offset = 0xAC;
    parameter[Unk_0xB0].offset = 0xB0;
    parameter[DamageMultiplier].offset = 0xB4;
    parameter[SwitchRegenSpeed].offset = 0xB8;
    for(int i=0;i<3;i++)
    {
        parameter[Unk_0xBC + i].offset = 0xBC + i;
        parameter[Unk_0xBF + i].offset = 0xBF + i;
        parameter[Unk_0xC2 + i].offset = 0xC2 + i;
        parameter[Unk_0xC5 + i].offset = 0xC5 + i;
        parameter[Unk_0xCF + i].offset = 0xCF + i;
    }
#endif

    Debug::Log("New GeneralParameter object constructed.", Debug::INFO, options);
}

/**Gets file data of this parameter file as a whole QByteArray.*/
QByteArray GeneralParameters::GetFileData()
{
    Debug::Log("GetFileData called.", Debug::INFO, options);
    return fileData;
}
/**Sets the entire parameter file data array at once to NewData, this should normally not be used.*/
void GeneralParameters::SetFileData(QByteArray NewData)
{
    Debug::Log("SetFileData called.", Debug::INFO, options);
    fileData = QByteArray(NewData);
}

bool GeneralParameters::GetFlagParameter(QCheckBox* Object)
{
    Debug::Log("GetFlagParameter called.", Debug::INFO, options);
    QObject* byte = Object->parent();
    int bit = Object->objectName().split('_').last().toUInt() - 1;

    if((void*)byte == (void*)parameter[FlagGroup].UiElement)
        return BitManipulation::Bit(*(constData + parameter[FlagGroup].offset + (int)(bit / 8)), bit % 8);
    if((void*)byte == (void*)parameter[FlagGroup + 1].UiElement)
        return BitManipulation::Bit(*(constData + parameter[FlagGroup + 1].offset + (int)(bit / 8)), bit % 8);
    if((void*)byte == (void*)parameter[FlagGroup + 2].UiElement)
        return BitManipulation::Bit(*(constData + parameter[FlagGroup + 2].offset + (int)(bit / 8)), bit % 8);
    if((void*)Object == (void*)parameter[GreatApeMode].UiElement)
        return BitManipulation::Bit(*(constData + parameter[GreatApeMode].offset), 2);

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
    for(int i=0;i<GeneralParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(constData + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return (unsigned char)-1;
}
unsigned char GeneralParameters::GetUByteParameter(QPushButton* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);

    for(int i=0;i<GeneralParameterCount;i++)
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
    for(int i=0;i<GeneralParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(int*)(constData + parameter[i].offset);
    }

    Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
    return -1;
}
float GeneralParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO, options);
    for(int i=0;i<GeneralParameterCount;i++)
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

    int bit = Object->objectName().split('_').last().toUInt() - 1;

    if((void*)byte == (void*)parameter[FlagGroup].UiElement)
        ChangeData(parameter[FlagGroup].offset + (int)(bit / 8), bit % 8, NewValue);

    else if((void*)byte == (void*)parameter[FlagGroup + 1].UiElement)
        ChangeData(parameter[FlagGroup + 1].offset + (int)(bit / 8), bit % 8, NewValue);

    else if((void*)byte == (void*)parameter[FlagGroup + 2].UiElement)
        ChangeData(parameter[FlagGroup + 2].offset + (int)(bit / 8), bit % 8, NewValue);

    else if((void*)Object == (void*)parameter[GreatApeMode].UiElement)
        ChangeData(parameter[GreatApeMode].offset, 2, NewValue);

    else Debug::Log("Object " + Object->objectName() + " not part of Parameters.", Debug::WARNING, options);
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
void GeneralParameters::SetUByteParameter(QPushButton* Object, unsigned char NewValue)
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
void GeneralParameters::SetUShortParameter(QSpinBox* Object, unsigned short NewValue)
{
    Debug::Log("SetUShortParameter called.", Debug::INFO, options);
    // There are no 2-Byte Parameters in this Parameter-section.
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING, options);
}
void GeneralParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    Debug::Log("SetIntParameter called.", Debug::INFO, options);
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
void GeneralParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO, options);
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
