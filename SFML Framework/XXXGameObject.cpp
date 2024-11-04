#include "stdafx.h"
#include "XXXGameObject.h"

XXXGameObject::XXXGameObject(const std::string& name)
{
}

XXXGameObject::~XXXGameObject()
{
}

sf::Vector2f XXXGameObject::GetPosition() const
{
    return position;
}

void XXXGameObject::SetPosition(const sf::Vector2f& pos)
{
    position = pos;
}

void XXXGameObject::SetScale(const sf::Vector2f& scale)
{
    this->scale = scale;
}

float XXXGameObject::GetRotation() const
{
    return rotation;
}

void XXXGameObject::SetRotation(float angle)
{
    rotation = angle;
}

void XXXGameObject::SetOrigin(Origins preset)
{
}

void XXXGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
}

void XXXGameObject::Init()
{
}

void XXXGameObject::Release()
{
}

void XXXGameObject::Reset()
{
}

void XXXGameObject::Update(float dt)
{
}

void XXXGameObject::Draw(sf::RenderWindow& window)
{
}
