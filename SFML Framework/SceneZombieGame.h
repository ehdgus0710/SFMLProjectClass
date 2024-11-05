#pragma once
#include "Scene.h"

class Player;
class Zombie;

class SceneZombieGame : public Scene
{
protected:
	Player* player;

	std::list<Zombie*> zombieList;
	ObjectPool<Zombie> zombiePool;

public:
	void SpawnZombies(int count);

public:
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;

public:
	SceneZombieGame();
	~SceneZombieGame();
};

