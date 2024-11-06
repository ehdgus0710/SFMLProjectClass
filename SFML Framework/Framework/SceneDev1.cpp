#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Enter()
{
	rect1.setSize({ 200.f, 100.f });
	rect1.setFillColor(sf::Color::Blue);
	Utils::SetOrigin(rect1, Origins::MC);

	rect2.setSize({ 200.f, 100.f });
	rect2.setFillColor(sf::Color::Green);
	Utils::SetOrigin(rect2, Origins::MC);
	Scene::Enter();

	cameraView = Framework::Instance().GetRenderWindow().getDefaultView();
	cameraView.setCenter({});
	
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	rect1.rotate(100.f * dt);

	sf::Vector2f mousePos = ScreenToWorld(InputMgr::GetMousePosition());
	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		rect2.setPosition(mousePos);
	}

	if (Utils::CheckCollision(rect1, rect2))
	{
		rect2.setFillColor(sf::Color::Red);
	}
	else
	{
		rect2.setFillColor(sf::Color::Green);
	}

	if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		if (Utils::PointInTransformBounds(rect1, rect1.getLocalBounds(), mousePos))
		{
			rect1.setFillColor(sf::Color::Red);
		}
		else
		{
			rect1.setFillColor(sf::Color::Blue);
		}
	}

	

	std::cout <<  InputMgr::GetAxis(Axis::Horizontal) << std::endl;
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	window.setView(cameraView);
	Scene::Draw(window);

	window.draw(rect1);
	window.draw(rect2);
}
