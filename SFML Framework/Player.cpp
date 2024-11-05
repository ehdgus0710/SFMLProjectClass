#include "stdafx.h"
#include "Player.h"
#include "Scene.h"
#include "Bullet.h"
#include "SceneZombieGame.h"

Player::Player(const std::string& name)
	: GameObject(name)
	, speed(500.f)
	, shootTimer(0.f)
	, shootDelay(0.5f)
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

void Player::Shoot()
{
	Bullet* bullet = sceneGame->TakeBullet();
	bullet->Fire(position, lookDirection, 500.f, 1);
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
	SetPosition(sf::Vector2f::zero);
	SetOrigin(Origins::MC);
	SetRotation(0.f);
	direction = sf::Vector2f::right;

	sceneGame = dynamic_cast<SceneZombieGame*>(SceneMgr::Instance().GetCurrentScene());
}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if(direction.SqrMagnitude() > 1.f)
		direction.Normalized();
	
	lookDirection = (sf::Vector2f)SceneMgr::Instance().GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition()) - position;
	lookDirection.Normalized();

	SetRotation(Utils::Angle(lookDirection));

	position += direction * speed * dt;

	position.x = Utils::Clamp(position.x, moveableRect.left, moveableRect.width);
	position.y = Utils::Clamp(position.y, moveableRect.top, moveableRect.height);

	SetPosition(position);

	shootTimer += dt;
	if (shootTimer > shootDelay && InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		Shoot();
		shootTimer = 0.f;
	}
}

sf::FloatRect Player::GetLocalBounds() const
{
	return  body.getLocalBounds();
}

sf::FloatRect Player::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
