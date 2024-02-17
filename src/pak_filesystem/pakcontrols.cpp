#include "pakcontrols.h"

PakControls::PakControls(QString FilePath)
{
    if(!FilePath.endsWith("pak", Qt::CaseInsensitive))
    {
        Debug::Log("PakControls: not a pak file.", Debug::ERROR);
        return;
    }

    QByteArray pakData = FileParse::ReadWholeFile(FilePath);

    if((unsigned char)pakData.at(0) != PAK_FIRST_BYTE)
    {
        Debug::Log("PakControls: bad pak file", Debug::ERROR);
        return;
    }

    int* start_of_pak = (int*)pakData.constData();

    // This is the offset for each known parameter type.
    // Offset in this context means how far inside the .pak each parameter is stored.
    // Note: NEXT is only used to calculate the data size of the movement parameters.
    paramOffset[PARAM_TYPE_GENERAL] = *( start_of_pak  + PARAM_OFFSET_GENERAL);    // General Parameter Offset Value
    paramOffset[PARAM_TYPE_MELEE] = *( start_of_pak  + PARAM_OFFSET_MELEE);        // Melee Parameters Offset Value
    paramOffset[PARAM_TYPE_KI_BLAST] = *( start_of_pak  + PARAM_OFFSET_KI_BLAST);  // Ki Blast Parameters Offset Value
    paramOffset[PARAM_TYPE_MOVEMENT] = *( start_of_pak  + PARAM_OFFSET_MOVEMENT);  // Movement Parameters Offset Value
    paramOffset[PARAM_TYPE_NEXT] = *( start_of_pak + PARAM_OFFSET_NEXT);           // Special Dialogue Data Offset Value

    // This is the size of each parameter data section.
    // Another way to look at these would be the file size of each parameter file.
    paramSize[PARAM_TYPE_GENERAL] = paramOffset[PARAM_TYPE_MELEE] - paramOffset[PARAM_TYPE_GENERAL];         // General Parameters data size
    paramSize[PARAM_TYPE_MELEE] = paramOffset[PARAM_TYPE_KI_BLAST] - paramOffset[PARAM_TYPE_MELEE];          // Melee Parameters data size
    paramSize[PARAM_TYPE_KI_BLAST] = paramOffset[PARAM_TYPE_MOVEMENT] - paramOffset[PARAM_TYPE_KI_BLAST];    // Ki Blast Parameters Data Size
    paramSize[PARAM_TYPE_MOVEMENT] = paramOffset[PARAM_TYPE_NEXT] - paramOffset[PARAM_TYPE_MOVEMENT];        // Movement Parameters Data Size

    // This is the actual data of the .pak, split into different parts.
    // These are the rest of the pak file. Only used for saving, as this data is unknown.
    LeftPak = QByteArray(pakData.left(paramOffset[PARAM_TYPE_GENERAL]));
    RightPak = QByteArray(pakData.right(pakData.size() - paramOffset[PARAM_TYPE_NEXT]));
    // These are the QByteArrays of the known Parameters
    paramData[PARAM_TYPE_GENERAL] = QByteArray(pakData.mid(paramOffset[PARAM_TYPE_GENERAL], paramSize[PARAM_TYPE_GENERAL]));
    paramData[PARAM_TYPE_MELEE] = QByteArray(pakData.mid(paramOffset[PARAM_TYPE_MELEE], paramSize[PARAM_TYPE_MELEE]));
    paramData[PARAM_TYPE_KI_BLAST] = QByteArray(pakData.mid(paramOffset[PARAM_TYPE_KI_BLAST], paramSize[PARAM_TYPE_KI_BLAST]));
    paramData[PARAM_TYPE_MOVEMENT] = QByteArray(pakData.mid(paramOffset[PARAM_TYPE_MOVEMENT], paramSize[PARAM_TYPE_MOVEMENT]));

    failed = false;
    Debug::Log("PakControls object constructed.", Debug::INFO);
}
QByteArray PakControls::GetPakData()
{
    Debug::Log("GetPakData called.", Debug::INFO);
    QByteArray output(LeftPak);
    output.append(paramData[PARAM_TYPE_GENERAL]);
    output.append(paramData[PARAM_TYPE_MELEE]);
    output.append(paramData[PARAM_TYPE_KI_BLAST]);
    output.append(paramData[PARAM_TYPE_MOVEMENT]);
    output.append(RightPak);
    return output;
}
QByteArray PakControls::GetParamData(ParameterType ParamType)
{
    Debug::Log("GetParamData called.", Debug::INFO);
    return paramData[ParamType];
}
void PakControls::UpdateParamData(ParameterType ParamType, QByteArray* Data)
{
    Debug::Log("UpdateParamData called.", Debug::INFO);
    if(Data->size() != paramData[ParamType].size())
    {
        Debug::Log("UpdateParamData: QByteArray doesn't match Parameter data size.\nData = " + QString::number(Data->size()) + " Bytes\nparamData = " + QString::number(paramData[ParamType].size()) + " Bytes", Debug::ERROR);
        return;
    }
    paramData[ParamType].replace(0, paramData[ParamType].size(), *Data);
}
void PakControls::SavePak(QString Path)
{
    Debug::Log("SavePak called.", Debug::INFO);
    QByteArray* fullData = new QByteArray(GetPakData());
    FileParse::WriteFile(Path, fullData);
}
bool PakControls::HasFailed()
{
    Debug::Log("HasFailed called.", Debug::INFO);
    return failed;
}
