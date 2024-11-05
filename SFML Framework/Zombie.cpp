#include "stdafx.h"
#include "Zombie.h"

#include "Player.h"
#include "Scene.h"

int Zombie::TotalTypes = (int)Types::Crawler;

Zombie::Zombie(const std::string& name)
	: GameObject(name)
	, maxHp(0)
	, hp(0)
	, speed(0.f)
	, damage(0)
	, attackInterval(0.f)
	, attackTimer(0.f)
	, player(nullptr)
{
}

void Zombie::SetType(Types type)
{
	types = type;

	switch (types)
	{
	case Zombie::Types::Bloater:
	{
		textureId = "graphics/bloater.png";
		speed = 100.f;
	}
		break;
	case Zombie::Types::Chaser: 
		{
		textureId = "graphics/chaser.png";
		speed = 300.f;
	}
		break;
	case Zombie::Types::Crawler:
	{
		textureId = "graphics/crawler.png";
		speed = 200.f;
	}
		break;
	default:
		break;
	}

	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset);
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Zombie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Zombie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Zombie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	//body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	SetPosition(position);
	SetRotation(rotation);
	SetScale(sf::Vector2f::one);
}

void Zombie::Update(float dt)
{
	if (player != nullptr && Utils::Distance(position, player->GetPosition()) > 20.f)
	{
		direction = Utils::GetNormal(player->GetPosition() - position);
		//direction = player->GetPosition() - position;
		//direction.Normalized();

		SetRotation(Utils::Angle(direction));
		SetPosition(position + direction * speed * dt);
	}

	
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
