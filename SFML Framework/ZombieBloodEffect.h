#pragma once

#include "SpriteGo.h"

class SceneZombieGame;

class ZombieBloodEffect : public SpriteGo
{
protected:
	SceneZombieGame* sceneGame;

	float lifeTime;
	float currentLifeTime;

public:
	void Init() override;
	void Update(float dt) override;
	void SetScene(SceneZombieGame* scene) { sceneGame = scene; }
public:
	ZombieBloodEffect(const std::string& texId = "", const std::string& name = "");
	~ZombieBloodEffect() = default;

};
