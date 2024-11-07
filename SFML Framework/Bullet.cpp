#include "stdafx.h"
#include "Bullet.h"
#include "SceneZombieGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
	, direction(sf::Vector2f::zero)
	, textureId("graphics/bullet.png")
	, speed(0.f)
	, damage(10)
	, sceneGame(nullptr)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(pos);
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Bullet::GetLocalBounds() const
{
	return  body.getLocalBounds();
}

sf::FloatRect Bullet::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void Bullet::Fire(const sf::Vector2f& position, const sf::Vector2f& direction, float speed, int damage)
{
	this->position = position;
	this->direction = direction;
	this->speed = speed;
	this->damage = damage;

	SetRotation(Utils::Angle(direction));
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/shoot.wav"));
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	sceneGame = dynamic_cast<SceneZombieGame*>(SceneMgr::Instance().GetCurrentScene());

	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::ML);
	SetPosition(position);
	SetRotation(rotation);
	SetScale(sf::Vector2f::one);
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
}

void Bullet::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
		return;

	debugBox.SetOutlineColor(sf::Color::Green);

	const auto& list = sceneGame->GetZombieList();

	for (auto& zombie : list)
	{
		if (!zombie->IsActive())
			continue;

		sf::FloatRect bounds = GetGlobalBounds();
		sf::FloatRect zombieBounds = zombie->GetGlobalBounds();

		if (bounds.intersects(zombieBounds))
		{
			debugBox.SetOutlineColor(sf::Color::Red);
			zombie->OnDamage(this, damage);
			sceneGame->ReturnBullet(this);
			break;
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
