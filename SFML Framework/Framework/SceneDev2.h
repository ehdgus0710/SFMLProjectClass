#pragma once
#include "Scene.h"
#include "json.hpp"

using json = nlohmann::json;

class SceneDev2 : public Scene
{
protected:

public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

