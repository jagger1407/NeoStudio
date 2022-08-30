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
    paramOffset[GENERAL] = *( start_of_pak  + GENERAL_OFFSET);    // General Parameter Offset Value
    paramOffset[MELEE] = *( start_of_pak  + MELEE_OFFSET);        // Melee Parameters Offset Value
    paramOffset[KI_BLAST] = *( start_of_pak  + KI_BLAST_OFFSET);  // Ki Blast Parameters Offset Value
    paramOffset[MOVEMENT] = *( start_of_pak  + MOVEMENT_OFFSET);  // Movement Parameters Offset Value
    paramOffset[NEXT] = *( start_of_pak + NEXT_OFFSET);           // Special Dialogue Data Offset Value

    // This is the size of each parameter data section.
    // Another way to look at these would be the file size of each parameter file.
    paramSize[GENERAL] = paramOffset[MELEE] - paramOffset[GENERAL];         // General Parameters data size
    paramSize[MELEE] = paramOffset[KI_BLAST] - paramOffset[MELEE];          // Melee Parameters data size
    paramSize[KI_BLAST] = paramOffset[MOVEMENT] - paramOffset[KI_BLAST];    // Ki Blast Parameters Data Size
    paramSize[MOVEMENT] = paramOffset[NEXT] - paramOffset[MOVEMENT];        // Movement Parameters Data Size

    // This is the actual data of the .pak, split into different parts.
    // These are the rest of the pak file. Only used for saving, as this data is unknown.
    LeftPak = QByteArray(pakData.left(paramOffset[GENERAL]));
    RightPak = QByteArray(pakData.right(pakData.size() - paramOffset[NEXT]));
    // These are the QByteArrays of the known Parameters
    paramData[GENERAL] = QByteArray(pakData.mid(paramOffset[GENERAL], paramSize[GENERAL]));
    paramData[MELEE] = QByteArray(pakData.mid(paramOffset[MELEE], paramSize[MELEE]));
    paramData[KI_BLAST] = QByteArray(pakData.mid(paramOffset[KI_BLAST], paramSize[KI_BLAST]));
    paramData[MOVEMENT] = QByteArray(pakData.mid(paramOffset[MOVEMENT], paramSize[MOVEMENT]));

    failed = false;
    Debug::Log("PakControls object constructed.", Debug::INFO);
}
QByteArray PakControls::GetPakData()
{
    Debug::Log("GetPakData called.", Debug::INFO);
    QByteArray output(LeftPak);
    output.append(paramData[GENERAL]);
    output.append(paramData[MELEE]);
    output.append(paramData[KI_BLAST]);
    output.append(paramData[MOVEMENT]);
    output.append(RightPak);
    return output;
}
QByteArray PakControls::GetParamData(ParameterType ParamType)
{
    Debug::Log("GetParamData called.", Debug::INFO);
    return paramData[ParamType];
}
void PakControls::UpdateParamData(ParameterType ParamType, QByteArray Data)
{
    Debug::Log("UpdateParamData called.", Debug::INFO);
    if(Data.size() != paramData[ParamType].size())
    {
        Debug::Log("UpdateParamData: QByteArray doesn't match Parameter data size.\nData = " + QString::number(Data.size()) + " Bytes\nparamData = " + QString::number(paramData[ParamType].size()) + " Bytes", Debug::ERROR);
        return;
    }
    paramData[ParamType].replace(0, paramData[ParamType].size(), Data);
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
