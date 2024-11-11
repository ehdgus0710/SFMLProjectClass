#pragma once

#include "TextGo.h"

class Player;
class SceneZombieGame;

class UiUpgrade : public GameObject
{
protected:
	std::vector<TextGo*> upgradeTextObjects;
	sf::Sprite background;
	std::string backgroundId;

	SceneZombieGame*	sceneGame;
	Player*				player;

	sf::Vector2f startPosition;
	sf::Vector2f textScale;

	typedef void (UiUpgrade::* UpgradeFunc)();
	UpgradeFunc upgradeFunc[6];

	int textCount;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetTextInfo();

	void OnUpgradeRateOfFire();
	void OnUpgradeClipSizeCnextReload();
	void OnUpgradeMaxHealth();
	void OnUpgradeRunSpeed();
	void OnUpgradeHealthPickups();
	void OnUpgradeAmmoPickups();
	void OnLocalize(Languages lange) override;
public:

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	UiUpgrade(const std::string& name = "");
	~UiUpgrade();

};

