#include "movementparameters.h"

MovementParameters::MovementParameters(QByteArray ParameterData)
{
    paramData = ParameterData;
    constData = paramData.data();
    if(paramData == nullptr || constData == nullptr)
    {
        Debug::Log("Construction of KiParameter object failed!", Debug::ERROR);
        return;
    }

    #if 1 // Defining all known parameter offsets
    for(int i=0;i<MovementParameterCount;i++)
        parameter[i].offset = i * 0x04;
    #endif

    Debug::Log("MovementParameters Object successfully constructed.", Debug::INFO);
}

QByteArray* MovementParameters::GetFileData()
{
    Debug::Log("GetFileData called.", Debug::INFO);
    return &paramData;
}

void MovementParameters::SetFileData(QByteArray NewData)
{
    Debug::Log("SetFileData called.", Debug::INFO);
    paramData = NewData;
}

int MovementParameters::GetIntParameter(QSpinBox* Object)
{
    Debug::Log("GetIntParameter called.", Debug::INFO);
    for(int i=DDC_Consumption;i<=DAscDDesc_Consumption;i++)
        if(Object == parameter[i].UiElement)
            return *(int*)(constData + parameter[i].offset);
    return -1;
}

float MovementParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    Debug::Log("GetFloatParameter called.", Debug::INFO);
    for(int i=0;i<MovementParameterCount;i++)
        if(Object == parameter[i].UiElement)
            return *(float*)(constData + parameter[i].offset);

    return -1;
}

void MovementParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    Debug::Log("GetIntParameter called.", Debug::INFO);
    for(int i=DDC_Consumption;i<=DAscDDesc_Consumption;i++)
        if(Object == parameter[i].UiElement)
            *(int*)(paramData.data() + parameter[i].offset) = NewValue;
}

void MovementParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    Debug::Log("SetFloatParameter called.", Debug::INFO);
    for(int i=0;i<MovementParameterCount;i++)
        if(Object == parameter[i].UiElement)
            *(float*)(paramData.data() + parameter[i].offset) = NewValue;
}
