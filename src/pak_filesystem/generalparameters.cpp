#include "generalparameters.h"

GeneralParameters::GeneralParameters(QByteArray ParameterData, Options* options)
{
    this->options = options;
    fileData = ParameterData;
    constData = fileData.constData();
    if(fileData == nullptr || constData == nullptr)
    {
        Debug::Log("Construction of GeneralParameter object failed!", Debug::ERROR, options);
        return;
    }
    Debug::Log("New GeneralParameter object constructed.", Debug::INFO, options);
}
bool GeneralParameters::GetFlagParameter(QCheckBox* Object)
{
    Debug::Log("GetFlagParameter called.", Debug::INFO, options);
    QObject* byte = Object->parent();
    int bit = Object->objectName().right(1).toUInt() - 1;
    for(int i=FlagByte;i<FlagByte + 9;i++)
    {
        if((long)byte == (long)UiElements[i]) return BitManipulation::Bit(*(constData + offset[i]), bit);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return false;
}
unsigned char GeneralParameters::GetUByteParameter(QSpinBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<GeneralParameterCount;i++)
    {
        if((long)Object == (long)UiElements[i]) return *(constData + offset[i]);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return (unsigned char)-1;
}
unsigned char GeneralParameters::GetUByteParameter(QComboBox* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    if((long)Object == (long)UiElements[ZSearch]) return *(constData + offset[ZSearch]);
    else if((long)Object == (long)UiElements[ZSearch]) return *(constData + offset[AuraColor]);
    else if((long)Object == (long)UiElements[StepInMove]) return *(constData + offset[StepInMove]);
    else if((long)Object == (long)UiElements[AuraColor]) return *(constData + offset[AuraColor]);
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return (unsigned char)-1;
}
unsigned char GeneralParameters::GetUByteParameter(QPushButton* Object)
{
    Debug::Log("GetUByteParameter called.", Debug::INFO, options);
    for(int i=FusionType;i<=CounterMove+2;i++)
    {
        if((long)Object == (long)UiElements[i]) return *(constData + offset[i]);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
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
        if((long)Object == (long)UiElements[i]) return *(int*)(constData + offset[i]);
    }

    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return -1;
}
float GeneralParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO, options);
    for(int i=MaxPowerModeDuration;i<=MeleeChargeSpeed;i++)
    {
        if((long)Object == (long)UiElements[i]) return *(float*)(constData + offset[i]);
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return -1;
}

void GeneralParameters::SetFlagParameter(QCheckBox* Object, bool NewValue)
{
    Debug::Log("SetFlagParameter called.", Debug::INFO, options);
    QObject* byte = Object->parent();
    int bit = Object->objectName().right(1).toUInt();
    for(int i=0;i<9;i++)
    {
        if((long)byte == (long)UiElements[i])
        {
            ChangeData(offset[i], bit, NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
}

void GeneralParameters::SetUByteParameter(QSpinBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    for(int i=0;i<GeneralParameterCount;i++)
    {
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(offset[i], NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
}
void GeneralParameters::SetUByteParameter(QComboBox* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    if((long)Object == (long)UiElements[ZSearch])
    {
        ChangeData(offset[ZSearch], NewValue);
        return;
    }
    else if((long)Object == (long)UiElements[ZSearch])
    {
        ChangeData(offset[AuraColor], NewValue);
        return;
    }
    else if((long)Object == (long)UiElements[StepInMove])
    {
        ChangeData(offset[StepInMove], NewValue);
        return;
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return;
}
void GeneralParameters::SetUByteParameter(QPushButton* Object, unsigned char NewValue)
{
    Debug::Log("SetUByteParameter called.", Debug::INFO, options);
    for(int i=FusionType;i<=CounterMove+2;i++)
    {
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(offset[i], NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
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
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(offset[i], NewValue);
            return;
        }
    }

    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return;
}
void GeneralParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO, options);
    for(int i=MaxPowerModeDuration;i<=MeleeChargeSpeed;i++)
    {
        if((long)Object == (long)UiElements[i])
        {
            ChangeData(offset[i], NewValue);
            return;
        }
    }
    Debug::Log("Object " + Object->objectName() + " not part of UiElements.", Debug::WARNING, options);
    return;
}
QByteArray GeneralParameters::GetFileData()
{
    return QByteArray(fileData);
}
void GeneralParameters::SetFileData(QByteArray NewData)
{
    fileData.replace(0, fileData.size(), NewData);
}
