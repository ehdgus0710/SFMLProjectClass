#pragma once

#include "DataTable.h"
#include "Item.h"

struct DataItem
{
	Item::ItemType	id;
	std::string		textureId;
	int				value;
};


class ItemTable : public DataTable
{
public:
	static DataItem undefined;

protected:
	std::unordered_map<Item::ItemType, DataItem> tableMap;
	std::string filePath = "tables/item_table.csv";
public:
	bool Load() override;
	void Release() override;


	const DataItem& Get(Item::ItemType id);
public:
	ItemTable();
	virtual ~ItemTable();
	ItemTable(const ItemTable& other) = delete;
	ItemTable& operator=(const ItemTable& other) = delete;
};