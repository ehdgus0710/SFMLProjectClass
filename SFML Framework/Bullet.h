#pragma once

class SceneZombieGame;

class Bullet : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId;

	SceneZombieGame* sceneGame;

	sf::Vector2f direction;
	float speed;
	int damage;

	DebugBox debugBox;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const  override;
	sf::FloatRect GetGlobalBounds() const override;

	void Fire(const sf::Vector2f& position, const sf::Vector2f& direction, float speed, int damage);

public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	Bullet(const std::string& name = "");
	~Bullet() = default;

	
};
