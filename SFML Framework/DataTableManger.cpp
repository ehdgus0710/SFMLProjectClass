#include "stdafx.h"
#include "DataTableManger.h"
#include "ZombieTable.h"

DataTableManger::~DataTableManger()
{
	Release();
}

void DataTableManger::Init()
{
	Release();

	tableMap.insert({ DataTable::Types::String, new StringTable() });
	tableMap.insert({ DataTable::Types::Zombie, new ZombieTable() });
	tableMap.insert({ DataTable::Types::Item, new ItemTable() });

	for (auto table : tableMap)
	{
		table.second->Load();
	}
}

void DataTableManger::Release()
{
	for (auto table : tableMap)
	{
		table.second->Release();
		delete table.second;
	}

	tableMap.clear();
}
