#pragma once

#include "DataTable.h"
#include "Zombie.h"

struct DataZombie
{
	Zombie::Types	id;
	std::string		textureId;
	int				maxHp;
	int				damage;
	float			speed;
};


class ZombieTable : public DataTable
{
public:
	static DataZombie undefined;

protected:
	std::unordered_map<Zombie::Types, DataZombie> tableMap;
	std::string filePath = "tables/zombie_table.csv";
public:
	bool Load() override;
	void Release() override;


	const DataZombie& Get(Zombie::Types id);
public:
	ZombieTable();;
	virtual ~ZombieTable();
	ZombieTable(const ZombieTable& other) = delete;
	ZombieTable& operator=(const ZombieTable& other) = delete;
};

