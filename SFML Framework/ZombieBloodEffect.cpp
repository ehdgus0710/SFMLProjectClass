#include "stdafx.h"
#include "ZombieBloodEffect.h"
#include "SceneZombieGame.h"

ZombieBloodEffect::ZombieBloodEffect(const std::string& texId, const std::string& name)
	: SpriteGo("graphics/blood.png", name)
	, lifeTime(5.f)
	, currentLifeTime(0.f)
	, sceneGame(nullptr)
{
}

void ZombieBloodEffect::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 1;
}

void ZombieBloodEffect::Update(float dt)
{
	currentLifeTime += dt;

	if (lifeTime <= currentLifeTime)
	{
		sceneGame->ReturnBloodEffect(this);
		currentLifeTime = 0.f;
	}
}
