#include "stdafx.h"
#include "SceneZombieGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

#include "Bullet.h"
#include "Item.h"

SceneZombieGame::SceneZombieGame()
	: Scene(SceneIds::Game)
	, player(nullptr)
	, tileMap(nullptr)
	, createItemTime(0.5f)
	, currentItemTime(0.f)
{
}

SceneZombieGame::~SceneZombieGame()
{
}

void SceneZombieGame::SpawnZombies(int count)
{


	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = zombiePool.Take();
		zombieList.push_back(zombie);

		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		zombie->SetType(zombieType);


		sf::Vector2f position = sf::Vector2f{ Utils::RandomRange(moveableRect.left, moveableRect.width) , Utils::RandomRange(moveableRect.top,moveableRect.height) };
		zombie->SetMapRect(moveableRect);
		zombie->SetPosition(position);

		AddGo(zombie);
	}
}

void SceneZombieGame::SpawnItem(int count)
{
	auto rect = tileMap->GetGlobalBounds();

	for (int i = 0; i < count; ++i)
	{
		Item* item = itemPool.Take();
		itemList.push_back(item);
		sf::Vector2f position = sf::Vector2f{ Utils::RandomRange(rect.left, rect.left + rect.width) , Utils::RandomRange(rect.top, rect.top + rect.height) };
		item->SetOrigin(Origins::MC);
		item->CreateItem(position);

		AddGo(item);
	}
}

Bullet* SceneZombieGame::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bulletList.push_back(bullet);
	AddGo(bullet);
	return bullet;
}

const sf::FloatRect SceneZombieGame::GetTileMapSize()
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	return rect;
}

void SceneZombieGame::OnZombieDie(Zombie* zombie)
{
	RemoveGo(zombie);
	zombiePool.Return(zombie);
	zombieList.remove(zombie);
}

void SceneZombieGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bulletList.remove(bullet);
}

void SceneZombieGame::Init()
{
	tileMap = AddGo(new TileMap("TileMap"));
	player = AddGo(new Player("Player"));
	player->SetOrigin(Origins::MC);

	Scene::Init();
}

void SceneZombieGame::Release()
{
	Scene::Release();
}

void SceneZombieGame::Enter()
{
	cameraView.setSize(Framework::Instance().GetWindowSizeFloat());
	cameraView.setCenter(0.f, 0.f);
	Scene::Enter();

	moveableRect = tileMap->GetGlobalBounds();
	auto cellSize = tileMap->GetCellSize();

	moveableRect.width += moveableRect.left - cellSize.x;
	moveableRect.height += moveableRect.top - cellSize.y;
	moveableRect.left += cellSize.x;
	moveableRect.top += cellSize.y;

	player->SetMoveableRect(moveableRect);
}

void SceneZombieGame::Exit()
{
	for (auto& iter : bulletList)
	{
		RemoveGo(iter);
		bulletPool.Return(iter);
	}
	bulletList.clear();

	for (auto& iter : zombieList)
	{
		RemoveGo(iter);
		zombiePool.Return(iter);
	}
	zombieList.clear();

	for (auto& iter : itemList)
	{
		RemoveGo(iter);
		itemPool.Return(iter);
	}
	bulletList.clear();
	Scene::Exit();
}

void SceneZombieGame::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(100);
	}

	if (player != nullptr)
	{
		cameraView.setCenter(player->GetPosition());
	}

	currentItemTime += dt;
	if (currentItemTime > createItemTime)
	{
		SpawnItem(1);
		currentItemTime = 0.f;
	}
}