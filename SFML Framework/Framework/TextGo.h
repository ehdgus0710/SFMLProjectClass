#pragma once
#include "GameObject.h"
class TextGo : public GameObject
{
protected:
	std::string fontId;

public:
	sf::Text text;

	TextGo(const std::string& fontId = "", const std::string& name = "");
	~TextGo() = default;

	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);
	float GetRotation() const override;
	void SetRotation(float angle) override;


	void CreateCollider() override;

	void Init() override;

	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void Draw(sf::RenderWindow& window) override;
};

