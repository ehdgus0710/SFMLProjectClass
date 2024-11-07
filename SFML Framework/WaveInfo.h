#pragma once
class WaveInfo
{
public:
	WaveInfo() = default;
	WaveInfo(int spwanCount, float spawnTime)
		: spwanCount(0)
		, totalSpawnCount(spwanCount)
		, isSpawnEnd(false)
		, spwanTime(spawnTime)
		, currentSpawnTime(0.f)
	{}
	~WaveInfo() = default;
public:
	int spwanCount;
	int totalSpawnCount;
	bool isSpawnEnd;
	float spwanTime;
	float currentSpawnTime;
};

