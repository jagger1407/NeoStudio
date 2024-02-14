#include "movementparameters.h"

MovementParameters::MovementParameters(QByteArray ParameterData)
{
    fileData = ParameterData;
    rawData = fileData.data();
    if(fileData == nullptr || rawData == nullptr)
    {
        Debug::Log("Construction of KiParameter object failed!", Debug::ERROR);
        return;
    }

    #if 1 // Defining all known parameter offsets
    for(int i=0;i<MovementParameterCount;i++)
        parameter[i].offset = i * 0x04;
    #endif
}

QByteArray MovementParameters::GetFileData()
{
    Debug::Log("GetFileData called.", Debug::INFO);
    return QByteArray(fileData);
}

void MovementParameters::SetFileData(QByteArray NewData)
{
    Debug::Log("SetFileData called.", Debug::INFO);
    fileData = NewData;
}

int MovementParameters::GetIntParameter(QSpinBox* Object)
{
    Debug::Log("GetIntParameter called.", Debug::INFO);
    for(int i=DDC_Consumption;i<=DAscDDesc_Consumption;i++)
        if(Object == (void*)parameter[i].UiElement) return *(int*)(rawData + parameter[i].offset);
    return -1;
}

float MovementParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO);
    for(int i=0;i<MovementParameterCount;i++)
        if(Object == (void*)parameter[i].UiElement) return *(float*)(rawData + parameter[i].offset);

    return -1;
}

void MovementParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    Debug::Log("GetIntParameter called.", Debug::INFO);
    for(int i=DDC_Consumption;i<=DAscDDesc_Consumption;i++)
        if(Object == (void*)parameter[i].UiElement) ChangeData(parameter[i].offset, NewValue);
}

void MovementParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO);
    for(int i=0;i<MovementParameterCount;i++)
        if(Object == (void*)parameter[i].UiElement) ChangeData(parameter[i].offset, NewValue);
}
