#include "stdafx.h"
#include "UiHub.h"

UiHub::UiHub(const std::string& name)
	: GameObject(name)
	, gaugeHpHaxSize({400.f, 50.f})
{
}

void UiHub::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiHub::SetRotation(float angle)
{
	rotation = angle;
}

void UiHub::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiHub::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiHub::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiHub::SetScore(int score)
{
	textScore.setString("SCORE : " + std::to_string(score));

	Utils::SetOrigin(textScore, Origins::TL);
}

void UiHub::SetHiScore(int score)
{
	textHighScore.setString("HI SCORE : " + std::to_string(score));
	Utils::SetOrigin(textHighScore, Origins::TR);
}

void UiHub::SetAmmo(int current, int total)
{
	textAmmo.setString(std::to_string(current) + " / " + std::to_string(total));
	Utils::SetOrigin(textAmmo, Origins::BL);
}

void UiHub::SetHp(int hp, int max)
{
	float value = float(hp) / max;
	gaugeHp.setSize({gaugeHpHaxSize.x * value , gaugeHpHaxSize.y});
}

void UiHub::SetWave(int wave)
{
	textWave.setString("WAVE : " + std::to_string(wave));
	Utils::SetOrigin(textWave, Origins::BL);
}

void UiHub::SetZombieCount(int count)
{
	textZombieCount.setString("ZOMBIE : " + std::to_string(count));
	Utils::SetOrigin(textZombieCount, Origins::BR);
}

void UiHub::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

}

void UiHub::Release()
{
}

void UiHub::Reset()
{
	unsigned int textSize = 50;
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");

	textScore.setFont(font);
	textHighScore.setFont(font);
	textAmmo.setFont(font);
	textWave.setFont(font);
	textZombieCount.setFont(font);

	textScore.setCharacterSize(textSize);
	textHighScore.setCharacterSize(textSize);
	textAmmo.setCharacterSize(textSize);
	textWave.setCharacterSize(textSize);
	textZombieCount.setCharacterSize(textSize);

	textScore.setFillColor(sf::Color::White);
	textHighScore.setFillColor(sf::Color::White);
	textAmmo.setFillColor(sf::Color::White);
	textWave.setFillColor(sf::Color::White);
	textZombieCount.setFillColor(sf::Color::White);

	Utils::SetOrigin(textScore, Origins::TL);;
	Utils::SetOrigin(textHighScore, Origins::TR);;
	Utils::SetOrigin(textAmmo, Origins::BL);;
	Utils::SetOrigin(textWave, Origins::BL);;
	Utils::SetOrigin(textZombieCount, Origins::BR);;


	iconAmmoIcon.setTexture(TEXTURE_MGR.Get("graphics/ammo_icon.png"));
	Utils::SetOrigin(iconAmmoIcon, Origins::BL);;


	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeFloat();

	float topY = 25.f;
	float BottomY = windowSize.y - 25.f;


	textScore.setPosition(25.f, topY);
	textHighScore.setPosition(windowSize.x - 25.f, topY);

	iconAmmoIcon.setPosition(25.f, BottomY);
	textAmmo.setPosition(150.f, BottomY);

	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpHaxSize);
	gaugeHp.setPosition(400.f, -gaugeHpHaxSize.y + BottomY);

	textWave.setPosition(windowSize.x - 600.f, BottomY);
	textZombieCount.setPosition(windowSize.x - 25.f, BottomY);


	SetScore(0);
	SetHiScore(0);
	SetAmmo(0,10);
	SetHp(1, 1);
	SetWave(0);
	SetZombieCount(0);
}

void UiHub::Update(float dt)
{
	
}

void UiHub::Draw(sf::RenderWindow& window)
{
	window.draw(textScore);
	window.draw(textHighScore);
	window.draw(textAmmo);
	window.draw(textWave);
	window.draw(textZombieCount);
	window.draw(iconAmmoIcon);
	window.draw(gaugeHp);
}
