#include "stdafx.h"
#include "SceneZombieGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

#include "Bullet.h"
#include "Item.h"
#include "UiHub.h"
#include "UiUpgrade.h"
#include "UiGameOver.h"
#include "ZombieBloodEffect.h"
#include "Collider.h"
#include <fstream>

SceneZombieGame::SceneZombieGame()
	: Scene(SceneIds::Game)
	, player(nullptr)
	, tileMap(nullptr)
	, defaultCreateItemTime(3.5f)
	, createItemTime(3.5f)
	, currentItemTime(0.f)
	, score(0)
	, maxScore(0)
	, waveIndex(0)
	, isUpgrade(true)
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
		item->SetPlayer(player);
		item->SetOrigin(Origins::MC);
		item->CreateItem(position);

		AddGo(item);
	}
}

void SceneZombieGame::CreateBloodEffect(const sf::Vector2f& position, float angle)
{
	ZombieBloodEffect* zombieBloodEffect = bloodEffectPool.Take();
	bloodEffectList.push_back(zombieBloodEffect);
	zombieBloodEffect->SetOrigin(Origins::MC);
	zombieBloodEffect->SetPosition(position);
	zombieBloodEffect->SetRotation(angle);
	zombieBloodEffect->SetScene(this);

	AddGo(zombieBloodEffect);
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

	CreateBloodEffect(zombie->GetPosition(), zombie->GetRotation() + 180.f);

	uiHub->SetZombieCount((int)zombieList.size());

	score += 10;
	if (maxScore < score)
	{
		maxScore = score;
		uiHub->SetHiScore(maxScore);
	}
	uiHub->SetScore(score);
}

void SceneZombieGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bulletList.remove(bullet);
}

void SceneZombieGame::ReturnItem(Item* item)
{
	RemoveGo(item);
	itemPool.Return(item);
	itemList.remove(item);
}

void SceneZombieGame::ReturnBloodEffect(ZombieBloodEffect* bloodEffect)
{
	RemoveGo(bloodEffect);
	bloodEffectPool.Return(bloodEffect);
	bloodEffectList.remove(bloodEffect);
}

void SceneZombieGame::OnPlayerDie()
{
	Framework::Instance().SetTimeScale(0.f);
	uiGameOver->SetActive(true);
	SaveScore();
}

void SceneZombieGame::CreateWave(WaveInfo* wave)
{
	waveInfos.push_back(wave);
}

void SceneZombieGame::StartWave()
{
	LoadInGameInfo();
	currentWaveInfo = *waveInfos[waveIndex++];
	uiHub->SetWave(waveIndex);
	uiUpgrade->SetActive(false);
	isUpgrade = false;
}

void SceneZombieGame::Init()
{
	tileMap = AddGo(new TileMap("TileMap"));
	player = AddGo(new Player("Player"));
	uiUpgrade = AddGo(new UiUpgrade("Player"));
	player->SetOrigin(Origins::MC);
	uiHub = AddGo(new UiHub("UIStatus"));
	uiGameOver = AddGo(new UiGameOver("fonts/zombiecontrol.ttf", "GameOver"));

	for (int i = 0; i < 10; ++i)
	{
		CreateWave(new WaveInfo((i + 1) * 10, 0.5f - (i * 0.03f)));
	}

	Scene::Init();
}

void SceneZombieGame::Release()
{
	int size = (int)waveInfos.size();
	for (int i = 0; i < size; ++i)
	{
		delete waveInfos[i];
	}
	waveInfos.clear();

	Scene::Release();
}

void SceneZombieGame::Enter()
{
	SoundMgr::Instance().SetBgmVolume(10.f);
	SoundMgr::Instance().SetSfxVolume(2.f);
	SoundMgr::Instance().PlayBgm(SOUNDBUFFER_MGR.Get("sound/cunning_city.mp3"));

	FRAMEWORK.GetRenderWindow().setMouseCursorVisible(false);
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);

	cameraView.setSize(Framework::Instance().GetWindowSizeFloat());
	cameraView.setCenter(0.f, 0.f);

	uiView = Framework::Instance().GetRenderWindow().getDefaultView();
	//uiView.setSize(Framework::Instance().GetWindowSizeFloat());
	uiView.setCenter(Framework::Instance().GetWindowSizeFloat() * 0.5f);
	Scene::Enter();

	moveableRect = tileMap->GetGlobalBounds();
	auto cellSize = tileMap->GetCellSize();

	moveableRect.width += moveableRect.left - cellSize.x;
	moveableRect.height += moveableRect.top - cellSize.y;
	moveableRect.left += cellSize.x;
	moveableRect.top += cellSize.y;

	uiGameOver->text.setCharacterSize(200);
	uiGameOver->text.setString("PRESS ENTER\nTO CONTINUE");
	uiGameOver->SetPosition(Framework::Instance().GetWindowSizeFloat() * 0.5f);
	uiGameOver->SetOrigin(Origins::MC);
	uiGameOver->SetActive(false);

	player->SetMoveableRect(moveableRect);
	player->ResetStatus();

	currentItemTime = defaultCreateItemTime;


	FRAMEWORK.SetTimeScale(0.f);

	LoadScore();
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
	itemList.clear();

	for (auto& iter : bloodEffectList)
	{
		RemoveGo(iter);
		bloodEffectPool.Return(iter);
	}
	bloodEffectList.clear();


	uiUpgrade->Release();

	SoundMgr::Instance().StopAllSfx();
	SoundMgr::Instance().StopBgm();
	Scene::Exit();

	FRAMEWORK.GetRenderWindow().setMouseCursorVisible(true);
}

void SceneZombieGame::Update(float dt)
{
	cursor.setPosition(ScreenToUI(InputMgr::GetMousePosition()));
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		Framework::Instance().SetTimeScale(1.f);
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	if (!currentWaveInfo.isSpawnEnd && currentWaveInfo.currentSpawnTime > currentWaveInfo.spwanTime)
	{
		currentWaveInfo.spwanCount++;
		currentWaveInfo.currentSpawnTime = 0.f;
 		SpawnZombies(1);
		uiHub->SetZombieCount((int)zombieList.size());

		if (currentWaveInfo.spwanCount >= currentWaveInfo.totalSpawnCount)
		{
			currentWaveInfo.isSpawnEnd = true;
		}
	}
	else
	{
		currentWaveInfo.currentSpawnTime += dt;
	}

	if (currentWaveInfo.isSpawnEnd && zombieList.size() == 0 && !isUpgrade)
	{
		uiUpgrade->SetActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		SaveScore();
		SaveInGameInfo();
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

	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		Collider::IsDebug = !Collider::IsDebug;
	}
}

void SceneZombieGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	const sf::View& saveView = window.getView();
	window.setView(uiView);
	window.draw(cursor);
	window.setView(saveView);

}

bool SceneZombieGame::SaveScore()
{
	std::string filename = "Socre.txt";

	std::ofstream outFile(filename);
	if (!outFile)
	{
		std::cerr << "Err!" << std::endl;
		return 1;
	}

	outFile << maxScore << std::endl;

	outFile.close();

	return false;
}

bool SceneZombieGame::LoadScore()
{
	std::string filename = "Socre.txt";
	std::ifstream inFile(filename);

	if (!inFile)
	{
		std::cerr << "Err!" << std::endl;
		return 1;
	}

	inFile >> maxScore;

	uiHub->SetHiScore(maxScore);

	inFile.close();
	return false;
}

bool SceneZombieGame::SaveInGameInfo()
{
	std::string filename = "InGameInfo.txt";

	std::ofstream outFile(filename);
	if (!outFile)
	{
		std::cerr << "Err!" << std::endl;
		return 1;
	}

	outFile << waveIndex << std::endl;

	return false;
}

bool SceneZombieGame::LoadInGameInfo()
{
	std::string filename = "InGameInfo.txt";
	std::ifstream inFile(filename);

	if (!inFile)
	{
		std::cerr << "Err!" << std::endl;
		return 1;
	}

	inFile >> waveIndex;

	Status playerStatus = player->GetCurrentStatus();
	

	inFile.close();



	return false;
}
