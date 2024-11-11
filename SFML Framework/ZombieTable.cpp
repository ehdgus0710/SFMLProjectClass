#include "stdafx.h"
#include "ZombieTable.h"
#include "rapidcsv.h"

DataZombie ZombieTable::undefined;

ZombieTable::ZombieTable()
    : DataTable(Types::Zombie)
{
}

ZombieTable::~ZombieTable()
{
}

bool ZombieTable::Load()
{
    Release();

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        auto row = doc.GetRow<std::string>(i);

        Zombie::Types id = (Zombie::Types)std::stoi(row[0]);
        if (tableMap.find(id) != tableMap.end())
            return false;

        tableMap[id].id = id;
        tableMap[id].textureId = row[1];
        tableMap[id].maxHp = std::stoi(row[2]);
        tableMap[id].speed = std::stof(row[3]);
        tableMap[id].damage = std::stoi(row[4]);

        // auto column = doc.GetColumn<std::string>(i);
    }

    return true;
}

void ZombieTable::Release()
{
    tableMap.clear();
}

const DataZombie& ZombieTable::Get(Zombie::Types id)
{
    auto find = tableMap.find(id);
    if (find == tableMap.end())
    {
        return undefined;
    }

    return find->second;
}