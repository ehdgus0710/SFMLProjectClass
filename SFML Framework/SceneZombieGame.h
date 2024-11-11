#pragma once
#include "Scene.h"
#include "WaveInfo.h"

class Player;
class TileMap;
class Zombie;
class Bullet;
class Item;
class UiHub;
class UiUpgrade;
class UiGameOver;
class ZombieBloodEffect;

class SceneZombieGame : public Scene
{
protected:
	Player* player;
	TileMap* tileMap;
	UiHub* uiHub;
	UiUpgrade* uiUpgrade;
	UiGameOver* uiGameOver;

	std::vector<WaveInfo*>	waveInfos;
	WaveInfo				currentWaveInfo;
	int						waveIndex;

	sf::Sprite cursor;

	std::list<Zombie*> zombieList;
	ObjectPool<Zombie> zombiePool;

	std::list<Bullet*> bulletList;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> itemList;
	ObjectPool<Item> itemPool;

	std::list<ZombieBloodEffect*> bloodEffectList;
	ObjectPool<ZombieBloodEffect> bloodEffectPool;

	sf::FloatRect moveableRect;

	float defaultCreateItemTime;
	float createItemTime;
	float currentItemTime;

	int score;
	int maxScore;

	bool isUpgrade;

public:
	void SpawnZombies(int count);
	void SpawnItem(int count);
	void CreateBloodEffect(const sf::Vector2f& position, float angle);
	Bullet* TakeBullet();
	const sf::FloatRect GetTileMapSize();

	const std::list<Zombie*>& GetZombieList() { return zombieList; }

	void OnZombieDie(Zombie* zombie);
	void ReturnBullet(Bullet* bullet);
	void ReturnItem(Item* item);
	void ReturnBloodEffect(ZombieBloodEffect* bloodEffect);

	void OnPlayerDie();
	void CreateWave(WaveInfo* wave);
	void StartWave();
	void SubItemSpawnTime(float time) { createItemTime -= time; }

public:
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool SaveScore();
	bool LoadScore();

	bool SaveInGameInfo();
	bool LoadInGameInfo();

public:
	SceneZombieGame();
	~SceneZombieGame();
};

