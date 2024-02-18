#include "movementparameters.h"

MovementParameters::MovementParameters(QByteArray ParameterData)
{
    paramData = ParameterData;
    constData = paramData.data();
    if(paramData == nullptr || constData == nullptr)
    {
        Debug::Log("Construction of KiParameter object failed! No data passed.", Debug::ERROR);
        return;
    }

    #if 1 // Defining all known parameter offsets
    for(int i=0;i<MovementParameterCount;i++)
        parameter[i].offset = i * 0x04;
    #endif

    Debug::Log("MovementParameters Object successfully constructed.", Debug::INFO);
}

QByteArray* MovementParameters::GetParameterData()
{
    return &paramData;
}

void MovementParameters::SetParameterData(QByteArray NewData)
{
    if(NewData.size() != paramData.size())
    {
        Debug::Log("SetFileData failed - Sizes don't match up.\n" \
            "Current Size: " + QString::number(paramData.size()) + " Bytes\t- New Size: " + QString::number(NewData.size()) + " Bytes", Debug::ERROR);
    }
    paramData = NewData;
    Debug::Log("MovementParameters Data set.", Debug::INFO);
}

int MovementParameters::GetIntParameter(QSpinBox* Object)
{
    for(int i=DDC_Consumption;i<=DAscDDesc_Consumption;i++)
        if(Object == parameter[i].UiElement)
            return *(int*)(constData + parameter[i].offset);
    return -1;
}

float MovementParameters::GetFloatParameter(QDoubleSpinBox* Object)
{
    for(int i=0;i<MovementParameterCount;i++)
        if(Object == parameter[i].UiElement)
            return *(float*)(constData + parameter[i].offset);

    return -1;
}

void MovementParameters::SetIntParameter(QSpinBox* Object, int NewValue)
{
    for(int i=DDC_Consumption;i<=DAscDDesc_Consumption;i++)
        if(Object == parameter[i].UiElement)
            *(int*)(paramData.data() + parameter[i].offset) = NewValue;
}

void MovementParameters::SetFloatParameter(QDoubleSpinBox* Object, float NewValue)
{
    for(int i=0;i<MovementParameterCount;i++)
        if(Object == parameter[i].UiElement)
            *(float*)(paramData.data() + parameter[i].offset) = NewValue;
}
