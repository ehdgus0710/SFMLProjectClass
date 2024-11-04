#pragma once
#include "GameObject.h"

class Bat;
class ScenePongGame;

class Ball : public GameObject
{
protected:
	sf::CircleShape		body;
	sf::FloatRect		movableBounds;

	sf::Vector2f		direction;
	Bat*				bat;
	ScenePongGame*			sceneGame;
	float				moveSpeed;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Fire(const sf::Vector2f& direction, float speed)
	{
		this->direction = direction;
		this->moveSpeed = speed;
		this->direction.Normalized();
	}

	void SetBat(Bat* bat) { this->bat = bat; }
	void SetSceneGame(ScenePongGame* scene) { this->sceneGame = scene; }
public:
	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	Ball(const std::string& name = "");
	~Ball() = default;
};

