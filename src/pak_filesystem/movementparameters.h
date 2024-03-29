#ifndef MOVEMENTPARAMETERS_H
#define MOVEMENTPARAMETERS_H

#include "src/neo_info.h"
#include "src/external/debug.h"

/**
 * @todo write docs
 */
class MovementParameters
{
public:
    typedef enum
    {
        RegMovSpeed,
        RegMovSpeedWater,
        CRMoveSpeed,
        CRMoveSpeedWater,
        DashSpeed,
        DashSpeedWater,
        DDC_Speed,
        DDF_Speed,
        DDRF_Speed,
        DAscDesc_Speed,
        StepInSpeed,
        BackstepSpeed,
        SidestepSpeed,
        JumpSpeed,
        DashJumpSpeed,
        LiftStrikeJumpSpeed,
        AscSpeed,
        DescSpeed,
        TeleportSpeed,
        AscAcceleration,
        DescAcceleration,
        Unk54,
        DashLength,
        Unk5C,
        Unk60,
        Unk64,
        JumpHeight,
        DashJumpHeight,
        DDC_Consumption,
        DDF_Consumption,
        DAscDDesc_Consumption,
        Unk7C,
        HDDTSC,
        Unk84,
        Unk88,
        Unk8C,
        Unk90,
        Unk94,
        VDDTSC,
        Unk9C,
        UnkA0,
        MovementParameterCount
    } MovementParameter;

    Param_Offset parameter[MovementParameterCount];

    MovementParameters(QByteArray ParameterData);

    int GetIntParameter(QSpinBox* Object);
    float GetFloatParameter(QDoubleSpinBox* Object);
    void SetIntParameter(QSpinBox* Object, int NewValue);
    void SetFloatParameter(QDoubleSpinBox* Object, float NewValue);
    /**
     * The parameter type of this parameter object.
     */
    const ParameterType paramType = PARAM_TYPE_MOVEMENT;
    QByteArray* GetParameterData();
    void SetParameterData(QByteArray NewData);
private:
    const char* constData = nullptr;
    QByteArray paramData;
};

#endif // MOVEMENTPARAMETERS_H
