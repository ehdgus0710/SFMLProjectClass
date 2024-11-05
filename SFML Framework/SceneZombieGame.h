#pragma once
#include "Scene.h"

class Player;
class TileMap;
class Zombie;
class Bullet;
class Item;

class SceneZombieGame : public Scene
{
protected:
	Player* player;
	TileMap* tileMap;


	std::list<Zombie*> zombieList;
	ObjectPool<Zombie> zombiePool;
	std::list<Bullet*> bulletList;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> itemList;
	ObjectPool<Item> itemPool;

	sf::FloatRect moveableRect;

	float createItemTime;
	float currentItemTime;

public:
	void SpawnZombies(int count);
	void SpawnItem(int count);
	Bullet* TakeBullet();
	const sf::FloatRect GetTileMapSize();
	TileMap* GetTileMap() { return tileMap; }

	const std::list<Zombie*>& GetZombieList() { return zombieList; }

	void OnZombieDie(Zombie* zombie);
	void ReturnBullet(Bullet* bullet);

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

