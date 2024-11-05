#pragma once

class SceneZombieGame;

class Player : public GameObject
{
protected:
	sf::Sprite			body;
	std::string			textureId;
	SceneZombieGame*	sceneGame;
	sf::FloatRect		moveableRect;

	sf::Vector2f		direction;
	sf::Vector2f		lookDirection;
	float				speed;

	int					maxHp;
	int					hp;

	float				shootTimer;
	float				shootDelay;
	float				maxDelayTime;
	float				defalutDelayTime;


public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetMoveableRect(const sf::FloatRect& rect) { moveableRect = rect; }
	sf::FloatRect GetLocalBounds() const  override;
	sf::FloatRect GetGlobalBounds() const override;

	void Shoot();

	void OnTakeDamage(int takeDamage);
	void AddHp(int hp);
	void AddDelayTime(float delay);

public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	Player(const std::string& name = "");
	~Player() = default;
};
