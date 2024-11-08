#pragma once

class Player;
class SceneZombieGame;

class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler
	};

	static int TotalTypes;
protected:

	sf::Sprite		body;
	Player*			player;
	Types			types = Types::Bloater;

	SceneZombieGame* sceneGame;

	sf::FloatRect	mapRect;
	std::string		textureId;
	sf::Vector2f	direction;

	int				maxHp;
	int				hp;
	float			speed;
	int				damage;
	float			attackInterval;
	float			attackTimer;

public:

	void SetType(Types type);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPlayer(Player* player) { this->player = player; }
	void SetMapRect(const sf::FloatRect& mapRect) { this->mapRect = mapRect; }

	sf::FloatRect GetLocalBounds() const  override;
	sf::FloatRect GetGlobalBounds() const override;
	void OnDamage(GameObject* target , int damge);

	void CreateCollider() override;
public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	Zombie(const std::string& name = "");
	~Zombie();
};
