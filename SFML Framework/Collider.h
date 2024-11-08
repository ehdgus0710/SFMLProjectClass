#pragma once

class Collider
{
public:
	sf::RectangleShape coliderRect;
	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Vector2f size;
	sf::Vector2f offSet;
	float rotation;

	sf::Vector2f originPosition;
	Origins originPreset;

	bool isActive;
	bool isCollion;
	static bool IsDebug;

public:
	void SetSize(const sf::Vector2f& size);
	void SetOffset(const sf::Vector2f& offset);
	void SetPosition(const sf::Vector2f pos);
	void SetScale(const sf::Vector2f& scale);
	void SetOrigin(Origins origin);
	void SetRotation(float angle);

	void Reset();
	void Draw(sf::RenderWindow& window);

	void SetCollision(bool col) { isCollion = col; }

public:
	Collider();
	Collider(const sf::Vector2f pos, const sf::Vector2f& size, const sf::Vector2f& scale = sf::Vector2f::one, const sf::Vector2f& offset = sf::Vector2f::zero);
	~Collider();


};