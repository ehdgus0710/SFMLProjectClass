#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"

GameObject::GameObject(const std::string& name)
	: name(name), originPreset(Origins::TL)
	, collider(nullptr)
{

}

GameObject::~GameObject()
{
	if (collider != nullptr)
		delete collider;
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::CreateCollider()
{
	collider = new Collider(position, scale);
	collider->Reset();
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}
