#include "stdafx.h"
#include "Player.h"
#include "Scene.h"
#include "Bullet.h"
#include "SceneZombieGame.h"
#include "Collider.h"

Player::Player(const std::string& name)
	: GameObject(name)
	, speed(500.f)
	, shootTimer(0.f)
	, shootDelay(0.5f)
	, maxHp(10000)
	, hp(0)
	, maxDelayTime(0.05f)
	, defalutDelayTime(0.5f)

{
	textureId = "graphics/player.png";
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
	CreateCollider();
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);

	if (collider)
	{
		collider->SetPosition(position);
	}
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

	if (collider)
	{
		collider->SetRotation(rotation);
	}
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
	if (collider)
	{
		collider->SetSize(scale);
	}
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

void Player::CreateCollider()
{
	collider = new Collider(position, scale);
	collider->SetOrigin(originPreset);
	collider->Reset();
}

void Player::Shoot()
{
	Bullet* bullet = sceneGame->TakeBullet();
	bullet->Fire(position, lookDirection, 500.f, 1);
}

void Player::OnTakeDamage(int takeDamage)
{
	hp -= takeDamage;

	if (hp <= 0)
	{
		Framework::Instance().SetTimeScale(0.f);
	}
}

void Player::AddHp(int hp)
{
	this->hp += hp;
	if (this->hp > maxHp)
	{
		this->hp = maxHp;
	}
}

void Player::AddDelayTime(float delay)
{
	shootDelay -= delay;
	if (shootDelay < maxDelayTime)
	{
		shootDelay = maxDelayTime;
	}
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

	hp = maxHp;
	shootDelay = defalutDelayTime;

	if (collider != nullptr)
	{
		collider->SetSize((sf::Vector2f)body.getTexture()->getSize());
		collider->SetScale({ 1.5f,1.5f });
		collider->Reset();
	}

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

	debugBox.SetBounds(body.getGlobalBounds());
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
	// debugBox.Draw(window);

	if (collider != nullptr)
		collider->Draw(window);
}
