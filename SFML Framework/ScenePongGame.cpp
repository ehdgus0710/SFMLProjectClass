#include "stdafx.h"
#include "ScenePongGame.h"
#include "Bat.h"
#include "Ball.h"
#include "TextGo.h"


ScenePongGame::ScenePongGame()
	: Scene(SceneIds::Game)
	, ball(nullptr)
	, bat(nullptr)
	, isBallActive(false)
	, isGameover(false)
	, score(0)
	, gameoverText(nullptr)
{
}


void ScenePongGame::AddScore()
{ 
	score += 10;

	scoreNumberString = std::to_string(score);
	scoreText->text.setString(scoreString + scoreNumberString);
}

void ScenePongGame::IsGameOver()
{
	isGameover = true;
	gameoverText->SetActive(true);

	Framework::Instance().SetTimeScale(0.f);
}

void ScenePongGame::Init()
{

	ResourceMgr<sf::Font>::Instance().Load("fonts/KOMIKAP_.ttf");

	bat = AddGo(new Bat("Bat"));
	ball = AddGo(new Ball("Ball"));
	scoreText = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Score"));
	gameoverText = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Gameover"));

	Scene::Init();
}

void ScenePongGame::Release()
{
	Scene::Release();
}

void ScenePongGame::Enter()
{
	ResourceMgr<sf::Font>::Instance().Load("fonts/KOMIKAP_.ttf");

	gameoverText->SetActive(false);
	gameoverText->text.setFont(ResourceMgr<sf::Font>::Instance().Get("fonts/KOMIKAP_.ttf"));
	gameoverText->text.setCharacterSize(100);
	gameoverText->text.setFillColor(sf::Color::Red);
	gameoverText->text.setString("Game Over\n Restart : Enter");
	gameoverText->SetPosition(Framework::Instance().GetWindowSizeFloat() * 0.5f);
	gameoverText->SetOrigin(Origins::MC);

	scoreText->text.setFont(ResourceMgr<sf::Font>::Instance().Get("fonts/KOMIKAP_.ttf"));
	scoreText->text.setCharacterSize(100);
	scoreText->text.setFillColor(sf::Color::White);


	ball->SetBat(bat);
	ball->SetSceneGame(this);
	isBallActive = false;
	isGameover = false;


	scoreString = "Score : ";
	score = 0;
	scoreNumberString = std::to_string(score);
	scoreText->text.setString(scoreString + scoreNumberString);


	Scene::Enter();
}

void ScenePongGame::Exit()
{
	ResourceMgr<sf::Font>::Instance().Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void ScenePongGame::Update(float dt)
{
	Scene::Update(dt);

	if (!isBallActive)
	{
		ball->SetPosition(bat->GetPosition());
	}

	if (isGameover && InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		Framework::Instance().SetTimeScale(1.f);
		SceneMgr::Instance().ChangeScene(SceneIds::Game);
	}

	if (!isBallActive && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		ball->Fire({ 1.f, -1.f }, 500.f);
		isBallActive = true;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::LShift))
	{
		Framework::Instance().SetTimeScale(3.f);
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::LShift))
	{
		Framework::Instance().SetTimeScale(1.f);
	}
}

void ScenePongGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void ScenePongGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void ScenePongGame::OnPreDraw()
{
	Scene::OnPreDraw();
}

void ScenePongGame::OnPostDraw()
{
	Scene::OnPostDraw();
}