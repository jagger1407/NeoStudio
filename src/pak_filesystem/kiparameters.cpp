#include "kiparameters.h"

KiParameters::KiParameters(QByteArray ParameterData, Options* options) : options(options)
{
    fileData = ParameterData;
    rawData = fileData.data();
    if(fileData == nullptr || rawData == nullptr)
    {
        Debug::Log("Construction of KiParameter object failed!", Debug::ERROR, options);
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
}

QByteArray KiParameters::GetFileData()
{
    Debug::Log("GetFileData called.", Debug::INFO, options);
    return QByteArray(fileData);
}
void KiParameters::SetFileData(QByteArray NewData)
{
    Debug::Log("SetFileData called.", Debug::INFO, options);
    fileData.replace(0, fileData.size(), NewData);
}

void KiParameters::setCurrentBlast(int BlastID)
{
    Debug::Log("setCurrentBlast called.", Debug::INFO, options);
    blastOffset = BlastID * KI_BLAST_ATTACK_SIZE;
}

unsigned char KiParameters::GetUByteParameter(QSpinBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(rawData + blastOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
    return (unsigned char)-1;
}

unsigned char KiParameters::GetUByteParameter(QComboBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(rawData + blastOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
    return (unsigned char)-1;
}


unsigned short KiParameters::GetUShortParameter(QSpinBox* Object)
{
    Debug::Log("GetUShortParameter called.", Debug::INFO, options);
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING, options);
    return (unsigned short)-1;
}

int KiParameters::GetIntParameter(QSpinBox* Object)
{
    Debug::Log("GetIntParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(int*)(rawData + blastOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
    return -1;
}

float KiParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(float*)( rawData + blastOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
    return (unsigned char)-1;
}

void KiParameters::SetUByteParameter(QSpinBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset + blastOffset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
}

void KiParameters::SetUByteParameter(QComboBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset + blastOffset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
}

void KiParameters::SetUShortParameter(QSpinBox* Object, short unsigned int NewValue)
{
    Debug::Log("SetUShortParameter called.", Debug::INFO, options);
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING, options);
}

void KiParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    Debug::Log("SetIntParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset + blastOffset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
}

void KiParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO, options);
    for(int i=0;i<KiParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(parameter[i].offset + blastOffset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR, options);
}
