#include "stdafx.h"
#include "Bat.h"

Bat::Bat(const std::string& name)
	: GameObject(name)
	, maxX(0.f)
	, minX(0.f)
	, speed(500.f)
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bat::SetScale(const sf::Vector2f& scale)
{
	SetScale(scale);
	body.setScale(scale);
}

void Bat::SetOrigin(Origins preset)
{
	originPreset = preset;
	if(originPreset != Origins::Custom)
		origin = Utils::SetOrigin(body, originPreset);
}

void Bat::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bat::Init()
{
	body.setSize(sf::Vector2f(100.f, 5.f));
	body.setFillColor(sf::Color::White);
	SetOrigin(Origins::TC);

	auto windowSize = FRAMEWORK.GetWindowSizeFloat();
	startPosition.x = windowSize.x * 0.5f;
	startPosition.y = windowSize.y - 20.f;

	auto halfWidth = body.getSize().x * 0.5f;

	minX = halfWidth;
	maxX = windowSize.x - halfWidth;
}

void Bat::Reset()
{
	direction = sf::Vector2f::zero;
	SetPosition(startPosition);
}

void Bat::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);

	auto newPos = position + direction * speed * dt;
	newPos.x = Utils::Clamp(newPos.x, minX, maxX);
	SetPosition(newPos);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
