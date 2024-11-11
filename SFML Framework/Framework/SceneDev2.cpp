#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"

#include <codecvt>

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{

	auto text = AddGo(new TextGo("fonts/D2Coding.ttc", "Scene Name 2"));

	text->sortingLayer = SortingLayers::UI;
	text->Set(25, sf::Color::White);
	text->SetString("Hi");

	auto text2 = AddGo(new TextGo("fonts/D2Coding.ttc", "Scene Name 2"));

	text2->sortingLayer = SortingLayers::UI;
	text2->Set(25, sf::Color::White);
	text2->SetPosition({ 0.f , 100.f });
	//text2->SetString(L"ÇÑ±¹¾î");
	text2->SetString("Hi");

	std::cout << "SceneDev2::Init()" << std::endl;

	Scene::Init();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;

	TEXTURE_MGR.Load("graphics/player.png");

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/player.png");
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
