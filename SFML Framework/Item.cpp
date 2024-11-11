#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "SceneZombieGame.h"
#include "Collider.h"
#include "ItemTable.h"

int Item::totalItemType = (int)ItemType::End;

Item::Item(const std::string& name)
	: GameObject(name)
	, itemType(ItemType::health)
	, value(1)
	, player(nullptr)
{
	CreateCollider();
}

void Item::SetTypeInfo()
{
	itemType = (ItemType)Utils::RandomRange(0, totalItemType - 1);

	auto dataItem = ITEM_TABLE->Get(itemType);

	textureId = dataItem.textureId;
	value = dataItem.value;

	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset); 
	if (collider != nullptr)
	{
		collider->SetSize((sf::Vector2f)body.getTexture()->getSize());
		collider->SetScale({ 0.6f,0.6f });
		collider->SetOrigin(Origins::MC);
		collider->SetOffset({ 2,2 });
		collider->Reset();
	}

}

void Item::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);

	if (collider)
	{
		collider->SetPosition(position);
	}
}

void Item::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

	if (collider)
	{
		collider->SetRotation(rotation);
	}
}

void Item::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

	if (collider)
	{
		collider->SetScale(scale);
	}
}

void Item::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Item::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);

}

void Item::CreateItem(const sf::Vector2f& position)
{
	SetTypeInfo();
	SetPosition(position);
}

void Item::CreateCollider()
{
	collider = new Collider(position, scale);
	collider->SetOrigin(originPreset);
	collider->Reset();
}

sf::FloatRect Item::GetLocalBounds() const
{
	return  body.getLocalBounds();
}

sf::FloatRect Item::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void Item::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Item::Release()
{
}

void Item::Reset()
{
	//body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	SetPosition(position);
	SetRotation(0.f);
	SetScale(sf::Vector2f::one);
}

void Item::Update(float dt)
{
}

void Item::FixedUpdate(float dt)
{
	if (player == nullptr)
		return;

	sf::FloatRect bounds = GetGlobalBounds();
	sf::FloatRect playerBounds = player->GetGlobalBounds();
	if (bounds.intersects(playerBounds))
	{
		if (itemType == ItemType::health)
			player->AddHp(value);
		else if (itemType == ItemType::Ammo)
			player->AddTotalAmmo(value);

		dynamic_cast<SceneZombieGame*>(SceneMgr::Instance().GetCurrentScene())->ReturnItem(this);
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	if(collider != nullptr)
		collider->Draw(window);
}
