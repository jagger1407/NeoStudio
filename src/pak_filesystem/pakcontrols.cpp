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

    for(int i=0;i<=PAK_SUB_COUNT;i++)
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
        Debug::Log("Section is invalid (Section Size: " + QString::number(sectionSize) + "), returning empty QByteArray.", Debug::WARNING);
        return QByteArray();
    }
    return pakData.mid(offsets[sectionID], sectionSize);
}

void PakControls::UpdateParamData(int sectionID, QByteArray* newData)
{
    int sectionSize = offsets[sectionID + 1] - offsets[sectionID];
    if(sectionSize < newData->length()) {
        Debug::Log("Size of newData is bigger than the section size inside the Pak. Resizing is not supported as of yet.", Debug::ERROR);
        return;
    }
    char* raw = newData->data();
    memcpy(pakData.data() + offsets[sectionID], raw, sectionSize);
}


void PakControls::SavePak(QString Path)
{
    FileParse::WriteFile(Path, &pakData);
    if(FileParse::DoesFileExist(Path))
        Debug::Log("File '" + Path + "' saved successfully.", Debug::INFO);
}
bool PakControls::HasFailed()
{
    return failed;
}

void PakControls::printSections()
{
    Debug::ConsolePrint("PAK TEST:\n------------------------------------", Debug::DEBUG);
    QStringList sectionNames = FileParse::ReadLines(g_Options.sectionNameFile);
    for(int i=0;i<PAK_SUB_COUNT;i++)
    {
        Debug::ConsolePrint(sectionNames[i] + " - Size: " + QString::number(offsets[i+1] - offsets[i]), Debug::DEBUG);
    }
    Debug::ConsolePrint("-----------------------------------------------", Debug::DEBUG);
}
