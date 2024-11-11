#include "stdafx.h"
#include "ItemTable.h"
#include "rapidcsv.h"

#include "Item.h"

DataItem ItemTable::undefined;

ItemTable::ItemTable()
	: DataTable(DataTable::Types::Item)
{
}

ItemTable::~ItemTable()
{
}

bool ItemTable::Load()
{
    Release();

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        auto row = doc.GetRow<std::string>(i);

        Item::ItemType id = (Item::ItemType)std::stoi(row[0]);
        if (tableMap.find(id) != tableMap.end())
            return false;

        tableMap[id].id = id;
        tableMap[id].textureId = row[1];
        tableMap[id].value = std::stoi(row[2]);
    }

    return true;
}

void ItemTable::Release()
{
    tableMap.clear();
}

const DataItem& ItemTable::Get(Item::ItemType id)
{
    auto find = tableMap.find(id);
    if (find == tableMap.end())
    {
        return undefined;
    }

    return find->second;
}