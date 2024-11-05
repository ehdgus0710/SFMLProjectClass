#pragma once

class Player;

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

public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	Zombie(const std::string& name = "");
	~Zombie() = default;
};
