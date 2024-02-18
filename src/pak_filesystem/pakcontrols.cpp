#include "pakcontrols.h"

PakControls::PakControls(QString FilePath)
{
    if(!FilePath.endsWith("pak", Qt::CaseInsensitive))
    {
        Debug::Log("PakControls: not a pak file.", Debug::ERROR);
        return;
    }

    pakData = FileParse::ReadWholeFile(FilePath);

    if((unsigned char)pakData.at(0) != PAK_SUB_COUNT)
    {
        Debug::Log("PakControls: bad pak file", Debug::ERROR);
        return;
    }

    int* start_of_pak = (int*)pakData.constData();

    int* offsetPtr = ((int*)pakData.constData()) + 1;

    for(int i=0;i<PAK_SUB_COUNT;i++)
    {
        offsets[i] = *offsetPtr++;
    }

    failed = false;
    Debug::Log("PakControls object constructed.", Debug::INFO);
}

QByteArray PakControls::GetParamData(int sectionID)
{
    int sectionSize = offsets[sectionID + 1] - offsets[sectionID];
    if(sectionSize <= 0)
    {
        Debug::Log("Section is empty (Section Size: " + QString::number(sectionSize) + "), returning empty QByteArray.", Debug::WARNING);
        return QByteArray();
    }
    return pakData.mid(offsets[sectionID], sectionSize);
}

void PakControls::UpdateParamData(int sectionID, QByteArray* newData)
{
    int sectionSize = offsets[sectionID + 1] - offsets[sectionID];
    char* raw = newData->data();
    memcpy(pakData.data() + offsets[sectionID], raw, sectionSize);
}


void PakControls::SavePak(QString Path)
{
    Debug::Log("SavePak called.", Debug::INFO);

    FileParse::WriteFile(Path, &pakData);
}
bool PakControls::HasFailed()
{
    Debug::Log("HasFailed called.", Debug::INFO);
    return failed;
}
