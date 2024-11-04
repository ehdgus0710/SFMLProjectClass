#include "stdafx.h"
#include "SceneZombieGame.h"
#include "Player.h"
#include "TileMap.h"

SceneZombieGame::SceneZombieGame()
	: Scene(SceneIds::Game)
{
}

SceneZombieGame::~SceneZombieGame()
{
}

void SceneZombieGame::Init()
{
	player = AddGo(new Player("Player"));
	AddGo(new TileMap("TileMap"));

	Scene::Init();
}

void SceneZombieGame::Release()
{
	Scene::Release();
}

void SceneZombieGame::Enter()
{
	Scene::Enter();
}

void SceneZombieGame::Exit()
{
	Scene::Exit();
}

void SceneZombieGame::Update(float dt)
{
	Scene::Update(dt);
}