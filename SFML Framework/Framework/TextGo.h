#pragma once
#include "GameObject.h"
class TextGo : public GameObject
{
protected:
	std::string fontId;
	std::string stringId;

public:
	sf::Text text;
	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);
	float GetRotation() const override;
	void SetRotation(float angle) override;

	void Set(int size, sf::Color color);
	void SetString(const std::string& id);

	void CreateCollider() override;

public:
	void Init() override;

	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void Draw(sf::RenderWindow& window) override;
	void OnLocalize(Languages lange) override;

public:

	TextGo(const std::string& fontId = "", const std::string& name = "");
	~TextGo() = default;

};

