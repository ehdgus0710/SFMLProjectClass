#include "stdafx.h"
#include "TextGo.h"
#include "Collider.h"

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

void TextGo::CreateCollider()
{
	collider = new Collider(position, scale);
	collider->SetOrigin(originPreset);
	collider->Reset();
}

void TextGo::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void TextGo::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	SetPosition(position);
	
	SetOrigin(originPreset);

	if (collider != nullptr)
		collider->Reset();
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	text.setPosition(pos);

	if (collider != nullptr)
		collider->SetPosition(pos);
}

void TextGo::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	text.setScale(scale);

	if (collider != nullptr)
		collider->SetScale(scale);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(text);

	if (collider != nullptr)
		collider->Draw(window);
}
