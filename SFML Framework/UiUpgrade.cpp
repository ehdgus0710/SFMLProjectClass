#include "stdafx.h"
#include "UiUpgrade.h"
#include "Collider.h"
#include "Scene.h"
#include "SceneZombieGame.h"
#include "Player.h"

UiUpgrade::UiUpgrade(const std::string& name)
	: GameObject(name)
	, textCount(6)
	, backgroundId("graphics/background.png")
{
}

UiUpgrade::~UiUpgrade()
{
	int size = (int)upgradeTextObjects.size();

	for (int i = 0; i < size; ++i)
	{
		delete upgradeTextObjects[i];
	}
	upgradeTextObjects.clear();
}

void UiUpgrade::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	background.setPosition(position);
	startPosition = position * 0.5f;

	int size = (int)upgradeTextObjects.size();

	for (int i = 0; i < size; ++i)
	{
		upgradeTextObjects[i]->SetPosition({ startPosition.x, startPosition.y + (float)i * textScale.y});
	}

}

void UiUpgrade::SetRotation(float angle)
{
	rotation = angle;
}

void UiUpgrade::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiUpgrade::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(background, originPreset);
	}
}

void UiUpgrade::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	background.setOrigin(origin);
}

void UiUpgrade::SetTextInfo()
{
	unsigned int textSize = 75;
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");

	for (int i = 0; i < textCount; ++i)
	{
		TextGo* text = new TextGo("fonts/zombiecontrol.ttf", std::to_string(i + 1));
		upgradeTextObjects.push_back(text);
		text->text.setFont(font);
		text->text.setCharacterSize(textSize);
		text->SetOrigin(Origins::MC);
		text->text.setFillColor(sf::Color::White);
		text->CreateCollider();
		text->Reset();
	}

	upgradeTextObjects[0]->text.setString("1- INCREASED RATE OF FIRE");
	upgradeTextObjects[1]->text.setString("2- INCREASED CLIP SIZECNEXT RELOAD");
	upgradeTextObjects[2]->text.setString("3- INCREASED MAX HEALTH");
	upgradeTextObjects[3]->text.setString("4- INCREASED RUN SPEED");
	upgradeTextObjects[4]->text.setString("5- MORE AND BETTER HEALTH PICKUPS");
	upgradeTextObjects[5]->text.setString("6- MORE AND BETTER AMMO PICKUPS");

	for (int i = 0; i < textCount; ++i)
	{
		auto size = upgradeTextObjects[i]->text.getGlobalBounds();
		upgradeTextObjects[i]->GetCollider()->SetSize({ size.width, size.height });
	}

	textScale.x = (float)textSize;
	textScale.y = (float)textSize;

}

void UiUpgrade::OnUpgradeRateOfFire()
{
	player->AddDelayTime(0.05f);
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/powerup.wav"));
}

void UiUpgrade::OnUpgradeClipSizeCnextReload()
{
	player->AddMaxAmmoCount(30);
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/powerup.wav"));
}

void UiUpgrade::OnUpgradeMaxHealth()
{
	player->AddMaxHp(20);
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/powerup.wav"));
}

void UiUpgrade::OnUpgradeRunSpeed()
{
	player->AddMoveSpeed(50.f);
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/powerup.wav"));
}

void UiUpgrade::OnUpgradeHealthPickups()
{
	sceneGame->SubItemSpawnTime(0.2f);
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/pickup.wav"));
}

void UiUpgrade::OnUpgradeAmmoPickups()
{
	sceneGame->SubItemSpawnTime(0.2f);
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/pickup.wav"));
}

void UiUpgrade::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 10;

	upgradeFunc[0] = &UiUpgrade::OnUpgradeRateOfFire;
	upgradeFunc[1] = &UiUpgrade::OnUpgradeClipSizeCnextReload;
	upgradeFunc[2] = &UiUpgrade::OnUpgradeMaxHealth;
	upgradeFunc[3] = &UiUpgrade::OnUpgradeRunSpeed;
	upgradeFunc[4] = &UiUpgrade::OnUpgradeHealthPickups;
	upgradeFunc[5] = &UiUpgrade::OnUpgradeAmmoPickups;

	
}

void UiUpgrade::Release()
{
	for (auto& iter : upgradeTextObjects)
	{
		delete iter;
	}
	upgradeTextObjects.clear();
}

void UiUpgrade::Reset()
{
	background.setTexture(TEXTURE_MGR.Get(backgroundId));
	SetTextInfo();
	SetPosition(Framework::Instance().GetWindowSizeFloat() * 0.5f);
	SetOrigin(Origins::MC);
	SetRotation(0.f);

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = (SceneZombieGame*)SCENE_MGR.GetCurrentScene();
}

void UiUpgrade::Update(float dt)
{
	sf::Vector2f mousePosition = SceneMgr::Instance().GetCurrentScene()->ScreenToUI(InputMgr::GetMousePosition());

	for (int i = 0; i < textCount; ++i)
	{
		if (upgradeTextObjects[i]->text.getGlobalBounds().contains(mousePosition))
		{
			upgradeTextObjects[i]->text.setFillColor(sf::Color::Red);

			if (InputMgr::GetMouseButton(sf::Mouse::Left))
			{
				(this->*upgradeFunc[i])();
				FRAMEWORK.SetTimeScale(1.f);
				sceneGame->StartWave();

				return;
			}
		}
		else
			upgradeTextObjects[i]->text.setFillColor(sf::Color::White);

	}
}

void UiUpgrade::FixedUpdate(float dt)
{
}

void UiUpgrade::Draw(sf::RenderWindow& window)
{
	window.draw(background);

	for (int i = 0; i < textCount; ++i)
	{
		upgradeTextObjects[i]->Draw(window);
	}
}
