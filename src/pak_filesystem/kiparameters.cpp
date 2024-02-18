#include "kiparameters.h"

KiParameters::KiParameters(QByteArray ParameterData)
{
    paramData = ParameterData;
    constData = paramData.constData();
    if(paramData == nullptr || constData == nullptr)
    {
        Debug::Log("Construction of KiParameter object failed! No data passed.", Debug::ERROR);
        return;
    }

    #if 1 // Defining all known parameter offsets
    parameter[Header].offset = 0x00;
    parameter[Damage].offset = 0x04;
    parameter[DamageGuarding].offset = 0x08;
    parameter[KiCost].offset = 0x0C;
    parameter[Speed].offset = 0x10;
    parameter[Spread].offset = 0x14;
    parameter[Range].offset = 0x18;
    parameter[Knockback].offset = 0x1C;
    parameter[Unk20].offset = 0x20;
    parameter[Hitstun].offset = 0x24;
    parameter[Unk25].offset = 0x25;
    parameter[Unk26].offset = 0x26;
    parameter[Unk27].offset = 0x27;
    parameter[Size].offset = 0x2A;
    parameter[Trail].offset = 0x2C;
    parameter[Unk30].offset = 0x30;
    parameter[Color].offset = 0x31;
    parameter[Amount].offset = 0x32;
    parameter[Trajectory].offset = 0x33;
    parameter[Footer].offset = 0x34;
    #endif

    Debug::Log("KiParameters object successfully constructed.", Debug::INFO);
}

QByteArray* KiParameters::GetParameterData()
{
    return &paramData;
}
void KiParameters::SetParameterData(QByteArray NewData)
{
    if(NewData.size() != paramData.size())
    {
        Debug::Log("SetFileData failed - Sizes don't match up.\n" \
            "Current Size: " + QString::number(paramData.size()) + " Bytes\t- New Size: " + QString::number(NewData.size()) + " Bytes", Debug::ERROR);
    }
    paramData = NewData;
    Debug::Log("KiParameters Data set.", Debug::INFO);
}

void KiParameters::setCurrentBlast(int BlastID)
{
    blastOffset = BlastID * KI_BLAST_ATTACK_SIZE;
}

unsigned char KiParameters::GetUByteParameter(QObject* Object)
{
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
            return *(unsigned char*)(paramData.data() + blastOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return (unsigned char)-1;
}

unsigned short KiParameters::GetUShortParameter(QSpinBox* Object)
{
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
    return (unsigned short)-1;
}

int KiParameters::GetIntParameter(QSpinBox* Object)
{
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
            return *(int*)(paramData.data() + blastOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return -1;
}

float KiParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
            return *(float*)( paramData.data() + blastOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return (unsigned char)-1;
}

void KiParameters::SetUByteParameter(QObject* Object, unsigned char NewValue)
{
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
        {
            *(unsigned char*)(paramData.data() + parameter[i].offset) = NewValue;
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}

void KiParameters::SetUShortParameter(QSpinBox* Object, short unsigned int NewValue)
{
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
}

void KiParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
        {
            *(int*)(paramData.data() + parameter[i].offset) = NewValue;
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}

void KiParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
        {
            *(float*)(paramData.data() + parameter[i].offset) = NewValue;
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
