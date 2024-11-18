#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"

#include <codecvt>
#include "AniPlayer.h"
#include "AniPlayer2.h"
#include "SaveLoadManager.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{
	// AddGo(new AniPlayer("Ani"));

	AddGo(new AniPlayer2("Ani"));
	// ResourceMgr<AnimationClip>().Load("")


	auto text = AddGo(new TextGo("fonts/D2Coding.ttc", "Scene Name 2"));

	//text->sortingLayer = SortingLayers::UI;
	//text->Set(25, sf::Color::White);
	//text->SetString("Hi");

	//auto text2 = AddGo(new TextGo("fonts/D2Coding.ttc", "Scene Name 2"));

	//text2->sortingLayer = SortingLayers::UI;
	//text2->Set(25, sf::Color::White);
	//text2->SetPosition({ 0.f , 100.f });
	////text2->SetString(L"ÇÑ±¹¾î");
	//text2->SetString("Hi");

	//std::cout << "SceneDev2::Init()" << std::endl;

	cameraView = Framework::Instance().GetRenderWindow().getDefaultView();
	cameraView.setCenter(sf::Vector2f::zero);

	Scene::Init();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;

	TEXTURE_MGR.Load("graphics/player.png");

	Scene::Enter();

	std::ifstream f("json/example.json");
	json data = json::parse(f);

	std::cout << data.at("pi").get<double>() << std::endl;
	std::cout << data["happy"] << std::endl;

	data.at("pi") = 0.0;
	std::cout << data.dump(4) << std::endl;
	// std::cout << data["happy"] << std::endl;
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

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SCENE_MGR.ChangeScene(SceneIds::Dev1);
	//}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SaveDataVC load = SaveLoadManager::Instance().Load();
		int gold = load.gold;
		int score = load.highscore;
		int version = load.version;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SaveDataVC save;
		save.highscore = 123;
		save.gold = 100;
		SaveLoadManager::Instance().Save(save);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
