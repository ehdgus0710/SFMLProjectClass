#pragma once
#include "GameObject.h"
class XXXGameObject : public GameObject
{
public:
	sf::Vector2f GetPosition() const;
	virtual void SetPosition(const sf::Vector2f& pos);\
	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& scale);


	virtual float GetRotation() const;
	virtual void SetRotation(float angle);

	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin);

public:
	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

public:
	XXXGameObject(const std::string& name);
	~XXXGameObject();

};

