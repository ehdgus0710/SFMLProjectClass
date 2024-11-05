#pragma once
#include "GameObject.h"
class Bat : public GameObject
{
protected:
	sf::RectangleShape	body;
	sf::Vector2f		direction;
	sf::Vector2f		startPosition;

	float				speed;
	float				minX;
	float				maxX;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); }

public:
	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	Bat(const std::string& name = "");
	~Bat() = default;
};

