#include "stdafx.h"
#include "Collider.h"

bool Collider::IsDebug = true;

void Collider::SetSize(const sf::Vector2f& size)
{
	this->size = size;
	coliderRect.setSize(size);
}

void Collider::SetOffset(const sf::Vector2f& offset)
{
	this->offSet = offset;
	coliderRect.setPosition(position + offset);
}

void Collider::SetPosition(const sf::Vector2f pos)
{
	position = pos;
	coliderRect.setPosition(position + offSet);
}

void Collider::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	coliderRect.setScale(scale);
}

void Collider::SetOrigin(Origins origin)
{
	this->originPreset = origin;
	originPosition = Utils::SetOrigin(coliderRect, originPreset);
}

void Collider::SetRotation(float angle)
{
	rotation = angle;
	coliderRect.setRotation(rotation);
}

void Collider::Reset()
{
	SetPosition(position);
	SetOffset(offSet);
	SetSize(size);
	SetScale(scale);
	SetOrigin(originPreset);
	SetRotation(rotation);
}

void Collider::Draw(sf::RenderWindow& window)
{
	if (isActive && IsDebug)
	{
		if(isCollion)
			coliderRect.setOutlineColor(sf::Color::Red);
		else
			coliderRect.setOutlineColor(sf::Color::Green);


		window.draw(coliderRect);

		isCollion = false;
	}
}

Collider::Collider()
	: position(sf::Vector2f::zero)
	, size(sf::Vector2f::one)
	, scale(sf::Vector2f::one)
	, offSet(sf::Vector2f::zero)
	, rotation(0.f)
	, isActive(true)
	, originPreset(Origins::MC)
	, isCollion(false)
{
	coliderRect.setFillColor(sf::Color::Transparent);
	coliderRect.setOutlineColor(sf::Color::Green);
	coliderRect.setOutlineThickness(1.f);
}

Collider::Collider(const sf::Vector2f pos, const sf::Vector2f& size, const sf::Vector2f& scale, const sf::Vector2f& offset)
	: position(pos)
	, size(size)
	, scale(scale)
	, offSet(offset)
	, rotation(0.f)
	, isActive(true)
	, originPreset(Origins::MC)
	, isCollion(false)
{
	coliderRect.setFillColor(sf::Color::Transparent);
	coliderRect.setOutlineColor(sf::Color::Green);
	coliderRect.setOutlineThickness(1.f);
}

Collider::~Collider()
{
}
