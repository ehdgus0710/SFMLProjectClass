#include "stdafx.h"
#include "Zombie.h"

#include "Player.h"
#include "Scene.h"
#include "SceneZombieGame.h"
#include "TileMap.h"

int Zombie::TotalTypes = (int)Types::Crawler;

Zombie::Zombie(const std::string& name)
	: GameObject(name)
	, maxHp(0)
	, hp(0)
	, speed(0.f)
	, damage(0)
	, attackInterval(2.f)
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
		maxHp = 50;
		speed = 100.f;
		damage = 1;
	}
		break;
	case Zombie::Types::Chaser: 
		{
		textureId = "graphics/chaser.png";
		maxHp = 20;
		speed = 300.f;
		damage = 2;
	}
		break;
	case Zombie::Types::Crawler:
	{
		textureId = "graphics/crawler.png";
		maxHp = 10;
		speed = 200.f;
		damage = 3;
	}
		break;
	default:
		break;
	}

	hp = maxHp;
	body.setTexture(TEXTURE_MGR.Get(textureId), true);

	SetOrigin(originPreset);
	sceneGame = dynamic_cast<SceneZombieGame*>(SceneMgr::Instance().GetCurrentScene());
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

sf::FloatRect Zombie::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Zombie::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void Zombie::OnDamage(GameObject* target, int d)
{
	hp -= d;
	if (hp <= 0)
	{
		sceneGame->OnZombieDie(this);
	}
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
	attackTimer = attackInterval;

}

void Zombie::Update(float dt)
{
	if (player != nullptr && Utils::Distance(position, player->GetPosition()) > 20.f)
	{
		direction = Utils::GetNormal(player->GetPosition() - position);
		SetRotation(Utils::Angle(direction));

		position.x = Utils::Clamp(position.x, mapRect.left, mapRect.width);
		position.y = Utils::Clamp(position.y, mapRect.top, mapRect.height);

		SetPosition(position + direction * speed * dt);
	}

	debugBox.SetBounds(body.getGlobalBounds());
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (player == nullptr)
		return;
	sf::FloatRect bounds = GetGlobalBounds();
	sf::FloatRect playerBounds = player->GetGlobalBounds();

	if (bounds.intersects(playerBounds))
	{
		debugBox.SetOutlineColor(sf::Color::Red);
		if (attackTimer > attackInterval)
		{
			attackTimer = 0.f;
			player->OnTakeDamage(damage);
		}
	}
	else
		debugBox.SetOutlineColor(sf::Color::Green);
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debugBox.Draw(window);
}
