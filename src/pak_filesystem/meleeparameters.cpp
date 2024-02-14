#include "meleeparameters.h"

MeleeParameters::MeleeParameters(QByteArray ParameterData)
{
    fileData = ParameterData;
    rawData = fileData.data();
    if(fileData == nullptr || rawData == nullptr)
    {
        Debug::Log("Construction of MeleeParameter object failed!", Debug::ERROR);
        return;
    }

#if 1 // Defining all known parameter offsets
    parameter[Header].offset = 0x00;
    parameter[SecondaryString].offset = 0x01;
    parameter[LockOnLoss].offset = 0x01;
    parameter[Damage].offset = 0x04;
    parameter[DamageGuarding].offset = 0x08;
    parameter[KiLoss].offset = 0x0C;
    parameter[KiGain].offset = 0x10;
    parameter[Unk14].offset = 0x14;
    parameter[Unk18].offset = 0x18;
    parameter[Unk1C].offset = 0x1C;
    parameter[Hitstun].offset = 0x20;
    parameter[Unk21].offset = 0x21;
    parameter[Unk22].offset = 0x22;
    parameter[Unk23].offset = 0x23;
    parameter[Unk24].offset = 0x24;
    parameter[Unk25].offset = 0x25;
    parameter[Unk26].offset = 0x26;
    parameter[Unk27].offset = 0x27;
    parameter[VFX].offset = 0x28;
    parameter[SFX].offset = 0x29;
    parameter[Unk2A].offset = 0x2A;
    parameter[Unk2B].offset = 0x2B;
    parameter[Knockback].offset = 0x2C;
    parameter[Unk30].offset = 0x30;
    parameter[Reach].offset = 0x34;
    parameter[Unk38].offset = 0x38;
    parameter[Unk3C].offset = 0x3C;
    parameter[Unk40].offset = 0x40;
    parameter[Unk44].offset = 0x44;
    parameter[Unk48].offset = 0x48;
    parameter[Unk4C].offset = 0x4C;
    parameter[Unk50].offset = 0x50;
    parameter[Unk54].offset = 0x54;
    parameter[Unk58].offset = 0x58;
    parameter[Unk5C].offset = 0x5C;
    parameter[EffectGuard].offset = 0x60;
    parameter[EffectCounter].offset = 0x61;
    parameter[GuardType].offset = 0x62;
    parameter[Unk63].offset = 0x63;
#endif

    Debug::Log("New MeleeParameter object constructed.", Debug::INFO);
}
QByteArray MeleeParameters::GetFileData()
{
    Debug::Log("GetFileData called.", Debug::INFO);
    return QByteArray(fileData);
}
void MeleeParameters::SetFileData(QByteArray NewData)
{
    Debug::Log("SetFileData called.", Debug::INFO);
    fileData.replace(0, fileData.size(), NewData);
}
void MeleeParameters::setCurrentAttack(int AttackID)
{
    Debug::Log("setCurrentAttack called.", Debug::INFO);
    attackOffset = AttackID * MELEE_ATTACK_SIZE;
}

bool MeleeParameters::GetFlagParameter(QCheckBox* Object)
{
    Debug::Log("GetFlagParameter called.", Debug::INFO);

    if(Object == (void*)parameter[SecondaryString].UiElement)
        return BitManipulation::Bit(*(rawData + attackOffset + parameter[SecondaryString].offset), 1);

    else if(Object == (void*)parameter[LockOnLoss].UiElement)
        return BitManipulation::Bit(*(rawData + attackOffset + parameter[LockOnLoss].offset), 2);

    else if(Object == (void*)parameter[GuardType].UiElement)
        return BitManipulation::Bit(*(rawData + attackOffset + parameter[GuardType].offset), 0);

    else
        Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);

    return false;
}
unsigned char MeleeParameters::GetUByteParameter(QSpinBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(rawData + attackOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
unsigned char MeleeParameters::GetUByteParameter(QComboBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(rawData + attackOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
unsigned short MeleeParameters::GetUShortParameter(QSpinBox* Object)
{
    Debug::Log("GetUShortParameter called.", Debug::INFO);
    // There are no 2-Byte Parameters in this Parameter-section.
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
    return (unsigned short)-1;
}
int MeleeParameters::GetIntParameter(QSpinBox* Object)
{
    Debug::Log("GetIntParameter called.", Debug::INFO);

    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(int*)(rawData + attackOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
float MeleeParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement) return *(float*)(rawData + attackOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
void MeleeParameters::SetFlagParameter(QCheckBox* Object, bool NewValue)
{
    Debug::Log("SetFlagParameter called.", Debug::INFO);
    if(Object == (void*)parameter[SecondaryString].UiElement)
        ChangeData(attackOffset + parameter[SecondaryString].offset, 1, NewValue);

    else if(Object == (void*)parameter[LockOnLoss].UiElement)
        ChangeData(attackOffset + parameter[LockOnLoss].offset, 2, NewValue);

    else if(Object == (void*)parameter[GuardType].UiElement)
        ChangeData(attackOffset + parameter[GuardType].offset, 0, NewValue);

    else
        Debug::Log("Object not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetUByteParameter(QSpinBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(attackOffset + parameter[i].offset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetUByteParameter(QComboBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(attackOffset + parameter[i].offset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetUShortParameter(QSpinBox* Object, unsigned short NewValue)
{
    Debug::Log("SetUShortParameter called.", Debug::INFO);
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
}
void MeleeParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    Debug::Log("SetIntParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(attackOffset + parameter[i].offset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == (void*)parameter[i].UiElement)
        {
            ChangeData(attackOffset + parameter[i].offset, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
