#include "stdafx.h"
#include "SceneZombieGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneZombieGame::SceneZombieGame()
	: Scene(SceneIds::Game)
	, player(nullptr)
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

		sf::Vector2f position = Utils::RandomInUnitCircle() * 500.f;
		zombie->SetPosition(position);

		AddGo(zombie);
	}
}

void SceneZombieGame::Init()
{
	player = AddGo(new Player("Player"));
	player->SetOrigin(Origins::MC);

	AddGo(new TileMap("TileMap"));

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
}

void SceneZombieGame::Exit()
{
	for (auto& iter : zombieList)
	{
		RemoveGo(iter);
		zombiePool.Return(iter);
	}
	zombieList.clear();

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
}