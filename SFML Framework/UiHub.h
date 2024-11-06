#pragma once

#include "TextGo.h"
#include "SpriteGo.h"

class UiHub : public GameObject
{
protected:
	sf::Text textScore;
	sf::Text textHighScore;
	sf::Text textAmmo;
	sf::Text textWave;
	sf::Text textZombieCount;

	sf::Sprite iconAmmoIcon;
	sf::RectangleShape gaugeHp;
	sf::Vector2f gaugeHpHaxSize;


public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetScore(int score);
	void SetHiScore(int score);
	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int wave);
	void SetZombieCount(int count);

public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	UiHub(const std::string& name = "");
	~UiHub() = default;

};
