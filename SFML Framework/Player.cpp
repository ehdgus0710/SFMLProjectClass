#include "stdafx.h"
#include "Player.h"
#include "Scene.h"
#include "Bullet.h"
#include "SceneZombieGame.h"
#include "Collider.h"
#include "UiHub.h"

Player::Player(const std::string& name)
	: GameObject(name)
	, shootTimer(0.f)
	, hp(0)
	, maxDelayTime(0.05f)
	, defaultDelayTime(0.5f)
	, InvulnerabilityTime(0.5f)
	, currentInvulnerabilityTime(0.f)
	, isInvulnerability(false)
	, currentAmmoCount(30)
	, totalAmmoCount(300)
	, reloadTime(1.5f)
	, damage(100)

{
	textureId = "graphics/player.png";
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
	CreateCollider();

	defaultStatus.maxHp = 10;
	defaultStatus.shootDelay = 0.3f;
	defaultStatus.speed = 500.f;
	defaultStatus.maxAmmoCount = 30;

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
	if ( currentAmmoCount == 0)
		return;
	--currentAmmoCount;
	Bullet* bullet = sceneGame->TakeBullet();
	bullet->Fire(position, lookDirection, 500.f, damage);
	uiHub->SetAmmo(currentAmmoCount, totalAmmoCount);
}

void Player::OnTakeDamage(int takeDamage)
{
	hp -= takeDamage;
	isInvulnerability = true;

	currentInvulnerabilityTime = InvulnerabilityTime;

	if (hp <= 0)
	{
		hp = 0;
		sceneGame->OnPlayerDie();
	}

	uiHub->SetHp(this->hp, currentStatus.maxHp);
}

void Player::AddHp(int hp)
{
	this->hp += hp;
	if (this->hp > currentStatus.maxHp)
	{
		this->hp = currentStatus.maxHp;
	}

	uiHub->SetHp(this->hp, currentStatus.maxHp);
}

void Player::AddDelayTime(float delay)
{
	currentStatus.shootDelay -= delay;
	if (currentStatus.shootDelay < maxDelayTime)
	{
		currentStatus.shootDelay = maxDelayTime;
	}
}

void Player::IsReload()
{
	if (isReload && totalAmmoCount == 0)
	{
		if(totalAmmoCount == 0)
			SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/reload_failed.wav"));
		return;
	}

	isReload = true;
	currentReloadTime = reloadTime;
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/reload.wav"));
}

void Player::OnReload()
{
	isReload = false;
	currentAmmoCount += currentStatus.maxAmmoCount > totalAmmoCount ? totalAmmoCount % currentStatus.maxAmmoCount : currentStatus.maxAmmoCount;
	
	if (currentAmmoCount > currentStatus.maxAmmoCount)
	{
		totalAmmoCount += currentAmmoCount - currentStatus.maxAmmoCount;
		currentAmmoCount = currentStatus.maxAmmoCount;
	}

	uiHub->SetAmmo(currentAmmoCount, totalAmmoCount);
}

void Player::IsCollision(bool isCollision)
{
	collider->SetCollision(isCollision);
}

sf::RectangleShape& Player::GetRectangleShape()
{
	return collider->coliderRect;
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

	currentStatus = defaultStatus;

	if (collider != nullptr)
	{
		collider->SetSize((sf::Vector2f)body.getTexture()->getSize());
		collider->SetScale({ 1.f,1.f });
		collider->Reset();
	}

	sceneGame = dynamic_cast<SceneZombieGame*>(SceneMgr::Instance().GetCurrentScene());

	uiHub = dynamic_cast<UiHub*>(sceneGame->FindGo("UIStatus"));
}

void Player::Update(float dt)
{
	if (hp <= 0)
		return;

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if(direction.SqrMagnitude() > 1.f)
		direction.Normalized();
	
	lookDirection = (sf::Vector2f)SceneMgr::Instance().GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition()) - position;
	lookDirection.Normalized();

	SetRotation(Utils::Angle(lookDirection));

	position += direction * currentStatus.speed * dt;

	position.x = Utils::Clamp(position.x, moveableRect.left, moveableRect.width);
	position.y = Utils::Clamp(position.y, moveableRect.top, moveableRect.height);

	SetPosition(position);

	shootTimer += dt;
	if (!isReload && shootTimer > currentStatus.shootDelay && InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		Shoot();
		shootTimer = 0.f;
	}

	if (isInvulnerability)
	{
		currentInvulnerabilityTime -= dt;

		if (currentInvulnerabilityTime <= 0.f)
			isInvulnerability = false;
	}

	if (isReload)
	{
		currentReloadTime -= dt;

		if (currentReloadTime <= 0.f)
		{
			OnReload();
		}
	}

	if (!isReload && InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		IsReload();
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

void Player::AddTotalAmmo(int count)
{ 
	totalAmmoCount += count;
	uiHub->SetAmmo(currentAmmoCount, totalAmmoCount);
}

void Player::ResetStatus()
{
	hp = currentStatus.maxHp;
	currentStatus.shootDelay = defaultDelayTime;
	currentInvulnerabilityTime = 0.f;
	isInvulnerability = false;

	currentAmmoCount = currentStatus.maxAmmoCount;
	totalAmmoCount = 300;

	uiHub->SetHp(hp, currentStatus.maxHp);
	uiHub->SetAmmo(currentAmmoCount, totalAmmoCount);

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	// debugBox.Draw(window);

	if (collider != nullptr)
		collider->Draw(window);
}
