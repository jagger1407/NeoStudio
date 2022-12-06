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
    attackOffset = AttackID * MELEE_ATTACK_SIZE;
}

bool MeleeParameters::GetFlagParameter(QCheckBox* Object)
{
    Debug::Log("GetFlagParameter called.", Debug::INFO);

    if((long)Object == (long)UiElements[SecondaryString]) return BitManipulation::Bit(*(rawData + attackOffset + offset[SecondaryString]), 1);
    else if((long)Object == (long)UiElements[LockOnLoss]) return BitManipulation::Bit(*(rawData + attackOffset + offset[LockOnLoss]), 2);
    else if((long)Object == (long)UiElements[GuardType]) return BitManipulation::Bit(*(rawData + attackOffset + offset[GuardType]), 0);
    else
    {
        Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    }

    return false;
}
unsigned char MeleeParameters::GetUByteParameter(QSpinBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if((long)Object == (long)UiElements[i]) return *(rawData + attackOffset + offset[i]);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
unsigned char MeleeParameters::GetUByteParameter(QComboBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if((long)Object == (long)UiElements[i]) return *(rawData + attackOffset + offset[i]);
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

    for(int i=0;i<Hitstun;i++)
    {
        if((long)Object == (long)UiElements[i]) return *(int*)(rawData + attackOffset + offset[i]);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
float MeleeParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO);
    for(int i=Knockback;i<EffectGuard;i++)
    {
        if((long)Object == (long)UiElements[i]) return *(float*)(rawData + attackOffset + offset[i]);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
    return 0;
}
void MeleeParameters::SetFlagParameter(QCheckBox* Object, bool NewValue)
{
    Debug::Log("SetFlagParameter called.", Debug::INFO);
    if((long)Object == (long)UiElements[SecondaryString]) ChangeData(attackOffset + offset[SecondaryString], NewValue);
    else if((long)Object == (long)UiElements[LockOnLoss]) ChangeData(attackOffset + offset[LockOnLoss], NewValue);
    else if((long)Object == (long)UiElements[GuardType]) ChangeData(attackOffset + offset[GuardType], NewValue);
    else
    {
        Debug::Log("Object not part of UiElements List.", Debug::ERROR);
    }
}
void MeleeParameters::SetUByteParameter(QSpinBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO);
    for(int i=0;i<MeleeParameterCount;i++)
    {
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(attackOffset + offset[i], NewValue);
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
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(attackOffset + offset[i], NewValue);
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
    for(int i=0;i<Hitstun;i++)
    {
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(attackOffset + offset[i], NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
void MeleeParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO);
    for(int i=Knockback;i<EffectGuard;i++)
    {
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(attackOffset + offset[i], NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements List.", Debug::ERROR);
}
