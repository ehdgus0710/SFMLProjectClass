#pragma once
#include "Scene.h"

class Bat;
class Ball;
class TextGo;

class ScenePongGame : public Scene
{
public:
	Bat*		bat;
	Ball*		ball;
	TextGo*		gameoverText;
	TextGo*		scoreText;

	std::string scoreNumberString;
	std::string scoreString;

	int score;

	bool isBallActive;
	bool isGameover;

public:
	void AddScore();
	void IsGameOver();

public:

	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Draw(sf::RenderWindow& window);
	void OnPreDraw() override;
	void OnPostDraw() override;

public:
	ScenePongGame();
	~ScenePongGame() = default;
};

