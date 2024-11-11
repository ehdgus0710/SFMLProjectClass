#include "stdafx.h"
#include "Zombie.h"

#include "Player.h"
#include "Scene.h"
#include "SceneZombieGame.h"
#include "TileMap.h"
#include "Collider.h"
#include "ZombieTable.h"

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

Zombie::~Zombie()
{
}

void Zombie::SetType(Types type)
{
	auto& data = ZOMBIE_TABLE->Get(type);

	types = data.id;
	textureId = data.textureId;
	maxHp = data.maxHp;
	speed = data.speed;
	damage = data.damage;

	hp = maxHp;
	body.setTexture(TEXTURE_MGR.Get(textureId), true);

	SetOrigin(originPreset);
	sceneGame = dynamic_cast<SceneZombieGame*>(SceneMgr::Instance().GetCurrentScene());

	if (collider != nullptr)
	{
		collider->SetSize((sf::Vector2f)body.getTexture()->getSize());
		collider->SetScale({ 1.f,1.f });
		collider->SetOrigin(originPreset);
		collider->Reset();
	}

}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	if (collider)
	{
		collider->SetPosition(pos);
	}
}

void Zombie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
	if (collider)
	{
		collider->SetRotation(angle);
	}
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

	if (collider)
	{
		collider->SetScale(scale);
	}
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
		SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/death.wav"));
	}
	else
		SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/hit.wav"));
}

void Zombie::CreateCollider()
{
	collider = new Collider(position, scale);
	collider->SetOrigin(originPreset);
	collider->Reset();
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	CreateCollider();
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
		if (Utils::CheckCollision(collider->coliderRect, player->GetCollider()->coliderRect))
		{
			player->IsCollision(true);
			collider->SetCollision(true);
			// debugBox.SetOutlineColor(sf::Color::Red);
			if (attackTimer > attackInterval)
			{
				attackTimer = 0.f;
				player->OnTakeDamage(damage);
			}
		}

	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);


	if (collider != nullptr)
		collider->Draw(window);
}
