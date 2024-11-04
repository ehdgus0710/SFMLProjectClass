#include "stdafx.h"
#include "Ball.h"

#include "Bat.h"
#include "ScenePongGame.h"

Ball::Ball(const std::string& name)
	: GameObject(name)
	, moveSpeed(0.f)
	, bat(nullptr)
	, sceneGame(nullptr)
{
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Ball::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	body.setScale(scale);
}

void Ball::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
		origin = Utils::SetOrigin(body, originPreset);
}

void Ball::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Ball::Init()
{
	float raidus = 10.f;
	body.setRadius(raidus);
	body.setFillColor(sf::Color::White);
	SetOrigin(Origins::BC);

	movableBounds = Framework::Instance().GetWindowBounds();
	movableBounds.left += raidus;
	movableBounds.width -= raidus;
	movableBounds.top += raidus * 2.f;
	movableBounds.height -= raidus * 2.f;
}

void Ball::Reset()
{
	direction = sf::Vector2f::zero;
	moveSpeed = 0.f;

	auto startPos = Framework::Instance().GetWindowSizeFloat();
	SetPosition({ startPos * 0.5f });

}

void Ball::Update(float dt)
{
	auto newPos = position + direction * moveSpeed * dt;

	if (newPos.y < movableBounds.top)
	{
		newPos.y = movableBounds.top;
		direction.y *= -1.f;
	}
	else if (newPos.y > movableBounds.top + movableBounds.height)
	{
		//newPos.y = movableBounds.top + movableBounds.height;
		//direction.y *= -1.f;
		sceneGame->IsGameOver();
	}

	if (newPos.x < movableBounds.left)
	{
		newPos.x = movableBounds.left;
		direction.x *= -1.f;
	}
	else if (newPos.x > movableBounds.left + movableBounds.width)
	{
		newPos.x = movableBounds.left + movableBounds.width;
		direction.x *= -1.f;
	}

	if (bat != nullptr)
	{
		auto batBounds = bat->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(batBounds))
		{
			newPos.y = batBounds.top;
			direction.y *= -1.f;

			if (sceneGame != nullptr)
				sceneGame->AddScore();
		}
	}

	SetPosition(newPos);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
