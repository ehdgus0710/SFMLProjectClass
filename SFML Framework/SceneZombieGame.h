#pragma once
#include "Scene.h"

class Player;

class SceneZombieGame : public Scene
{
protected:
	Player* player;

public:

	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;

public:
	SceneZombieGame();
	~SceneZombieGame();
};

