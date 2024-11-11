#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

std::wstring StringTable::Undefined = L"Undefined Id";

StringTable::StringTable()
    : DataTable(Types::String)
{
    stringTables.resize((int)Languages::Count);
    languageString.resize((int)Languages::Count);
    currentStringTableMap = &stringTables[(int)Variables::currentLanguge];
    for (int i = 0; i < (int)Languages::Count; ++i)
    {
        switch ((Languages)i)
        {
        case Languages::Korean:
            languageString[i] = "_Korean";
            break;
        case Languages::English:
            languageString[i] = "_English";
            break;
        case Languages::Japanese:
            languageString[i] = "_Japanese";
            break;
        case Languages::Count:
            break;
        default:
            break;
        }
    }
    
}

StringTable::~StringTable()
{
}

const std::wstring& StringTable::Get(const std::string& id, Languages language)
{
    auto iter = stringTables[(int)Variables::currentLanguge].find(id);

    if (iter == stringTables[(int)Variables::currentLanguge].end())
    {
        return Undefined;
    }
    
    return iter->second;
}

const std::wstring& StringTable::Get(const std::string& id)
{
    auto iter = stringTables[(int)Variables::currentLanguge].find(id);

    if (iter == stringTables[(int)Variables::currentLanguge].end())
    {
        return Undefined;
    }

    return iter->second;
}

std::string StringTable::LoadFilePath(int languagesIndex)
{
    std::string filePathLanguages = filePath;
    int pos = (int)filePathLanguages.find('.');
    filePathLanguages.insert(pos, languageString[languagesIndex]);
    return filePathLanguages;
}

bool StringTable::Load()
{
    if (!stringTables[(int)Variables::currentLanguge].empty())
        return false;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    int currentLangugeIndex = (int)Variables::currentLanguge;
    currentStringTableMap = &stringTables[currentLangugeIndex];

    rapidcsv::Document doc(LoadFilePath(currentLangugeIndex), rapidcsv::LabelParams(0, -1));

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        auto strings = doc.GetRow<std::string>(i);
        auto iter = stringTables[currentLangugeIndex].find(strings[0]);
        if (iter != stringTables[currentLangugeIndex].end())
        {
            std::cout << "스트링 테이블 키 중복" << std::endl;
            return false;
        }

        currentStringTableMap->insert({ strings[0], converter.from_bytes(strings[1]) });
    }
    return true;
}

void StringTable::Release()
{
    stringTables.clear();
}
