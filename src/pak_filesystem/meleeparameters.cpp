#include "meleeparameters.h"

MeleeParameters::MeleeParameters(QByteArray ParameterData)
{
    paramData = ParameterData;
    constData = paramData.constData();
    if(paramData == nullptr || constData == nullptr)
    {
        Debug::Log("Construction of MeleeParameter object failed! No data passed.", Debug::ERROR);
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

    Debug::Log("MeleeParameters object successfully constructed.", Debug::INFO);
}
QByteArray* MeleeParameters::GetParameterData()
{
    return &paramData;
}
void MeleeParameters::SetParameterData(QByteArray NewData)
{
    if(NewData.size() != paramData.size())
    {
        Debug::Log("SetFileData failed - Sizes don't match up.\n" \
            "Current Size: " + QString::number(paramData.size()) + " Bytes\t- New Size: " + QString::number(NewData.size()) + " Bytes", Debug::ERROR);
    }
    paramData = NewData;
    Debug::Log("MeleeParameters Data set.", Debug::INFO);
}
void MeleeParameters::setCurrentAttack(int AttackID)
{
    attackOffset = AttackID * MELEE_ATTACK_SIZE;
}

bool MeleeParameters::GetFlagParameter(QCheckBox* Object)
{
    if(Object == parameter[SecondaryString].UiElement)
        return BitManipulation::Bit(*(constData + attackOffset + parameter[SecondaryString].offset), 1);

    else if(Object == parameter[LockOnLoss].UiElement)
        return BitManipulation::Bit(*(constData + attackOffset + parameter[LockOnLoss].offset), 2);

    else if(Object == parameter[GuardType].UiElement)
        return BitManipulation::Bit(*(constData + attackOffset + parameter[GuardType].offset), 0);

    else
        Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);

    return false;
}
unsigned char MeleeParameters::GetUByteParameter(QObject* Object)
{
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == parameter[i].UiElement) return *(unsigned char*)(constData + attackOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
unsigned short MeleeParameters::GetUShortParameter(QSpinBox* Object)
{
    // There are no 2-Byte Parameters in this Parameter-section.
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
    return (unsigned short)-1;
}
int MeleeParameters::GetIntParameter(QSpinBox* Object)
{
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == parameter[i].UiElement) return *(int*)(constData + attackOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
float MeleeParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == parameter[i].UiElement) return *(float*)(constData + attackOffset + parameter[i].offset);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
void MeleeParameters::SetFlagParameter(QCheckBox* Object, bool NewValue)
{
    if(Object == parameter[SecondaryString].UiElement)
        BitManipulation::SetBit(paramData.data() + attackOffset + parameter[SecondaryString].offset, 1, NewValue);

    else if(Object == parameter[LockOnLoss].UiElement)
        BitManipulation::SetBit(paramData.data() + attackOffset + parameter[LockOnLoss].offset, 2, NewValue);

    else if(Object == parameter[GuardType].UiElement)
        BitManipulation::SetBit(paramData.data() + attackOffset + parameter[GuardType].offset, 0, NewValue);

    else
        Debug::Log("Object not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetUByteParameter(QObject* Object, unsigned char NewValue)
{
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
        {
            *(unsigned char*)(paramData.data() + attackOffset + parameter[i].offset) = NewValue;
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetUShortParameter(QSpinBox* Object, unsigned short NewValue)
{
    Debug::Log("This Parameter type does not have any 2-Byte variables, this method shouldn't have been called.", Debug::WARNING);
}
void MeleeParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
        {
            *(int*)(paramData.data() + attackOffset + parameter[i].offset) = NewValue;
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if(Object == parameter[i].UiElement)
        {
            *(float*)(paramData.data() + attackOffset + parameter[i].offset) = NewValue;
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
