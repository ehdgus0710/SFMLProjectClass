#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& fontId, const std::string& name)
	: GameObject(name), fontId(fontId)
{
}

void TextGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(text, originPreset);
}

void TextGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

float TextGo::GetRotation() const
{
	return rotation;
}

void TextGo::SetRotation(float angle)
{
	text.setRotation(angle);
	rotation = angle;
}

void TextGo::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	SetOrigin(originPreset);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	text.setPosition(pos);
}

void TextGo::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	text.setScale(scale);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(text);
}
