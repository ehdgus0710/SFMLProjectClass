#include "stdafx.h"
#include "Player.h"
#include "Scene.h"

Player::Player(const std::string& name)
	: GameObject(name)
	, speed(500.f)
{
	textureId = "graphics/player.png";
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(newOrigin);

}

void Player::Init()
{
}

void Player::Release()
{
}

void Player::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(originPreset);
	SetPosition(sf::Vector2f::zero);
	SetRotation(0.f);
	direction = sf::Vector2f::right;
}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if(direction.SqrMagnitude() > 1.f)
		direction.Normalized();
	
	lookDirection = (sf::Vector2f)SceneMgr::Instance().GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition()) - position;
	SetRotation(Utils::Angle(Utils::GetNormal(lookDirection)));

	SetPosition(position + direction * speed * dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
