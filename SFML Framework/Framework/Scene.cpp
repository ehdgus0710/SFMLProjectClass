#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	: id(id)
{
}

void Scene::Init()
{
	ApplyAddGo();
	ApplyRemoveGO();

	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
		// obj->OnLocalize(Variables::currentLanguge);
	}
}

void Scene::Exit()
{
	ApplyAddGo();
	ApplyRemoveGO();

	TEXTURE_MGR.UnloadAll();
	FONT_MGR.UnloadAll();
	SOUNDBUFFER_MGR.UnloadAll();
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->Update(dt);
	}


	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		Variables::currentLanguge = Languages::Korean;
		STRING_TABLE->Load();
		OnLocalize(Variables::currentLanguge);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		Variables::currentLanguge = Languages::English;
		STRING_TABLE->Load();
		OnLocalize(Variables::currentLanguge);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		Variables::currentLanguge = Languages::Japanese;
		STRING_TABLE->Load();
		OnLocalize(Variables::currentLanguge);
	}

}

void Scene::LateUpdate(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->LateUpdate(dt);
	}
}

void Scene::FixedUpdate(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->FixedUpdate(dt);
	}
}

void Scene::OnPreDraw()
{
	ApplyAddGo();
	ApplyRemoveGO();
}

void Scene::OnLocalize(Languages langugage)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;


		obj->OnLocalize(langugage);
	}
}


void Scene::Draw(sf::RenderWindow& window)
{
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawQueue;
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawUiQueue;

	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;

		if (obj->sortingLayer >= SortingLayers::UI)
		{
			drawUiQueue.push(obj);
		}

		else
		{
			drawQueue.push(obj);
		}
	}

	const sf::View& saveView = window.getView();
	window.setView(cameraView);

	while (!drawQueue.empty())
	{
		GameObject* obj = drawQueue.top();
		obj->Draw(window);
		drawQueue.pop();
	}

	window.setView(uiView);
	while (!drawUiQueue.empty())
	{
		GameObject* obj = drawUiQueue.top();
		obj->Draw(window);
		drawUiQueue.pop();
	}

	window.setView(saveView);
}

void Scene::OnPostDraw()
{
	ApplyAddGo();
	ApplyRemoveGO();
}

void Scene::RemoveGo(GameObject* obj)
{
	removeGameObjects.push_back(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	list.clear();
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			list.push_back(obj);
		}
	}
	return (int)list.size();
}

void Scene::ApplyAddGo()
{
	for (auto go : addGameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addGameObjects.clear();
}

void Scene::ApplyRemoveGO()
{
	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return Framework::Instance().GetRenderWindow().mapPixelToCoords(screenPos, cameraView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f screenPos)
{
	return Framework::Instance().GetRenderWindow().mapCoordsToPixel(screenPos, cameraView);
}

sf::Vector2f Scene::ScreenToUI(sf::Vector2i screenPos)
{
	return Framework::Instance().GetRenderWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UIToScreen(sf::Vector2f screenPos)
{
	return Framework::Instance().GetRenderWindow().mapCoordsToPixel(screenPos, uiView);
}

sf::Vector2f Scene::ScreenToWorld(const sf::View& view, sf::Vector2i screenPos)
{
	return Framework::Instance().GetRenderWindow().mapPixelToCoords(screenPos, view);
}

sf::Vector2i Scene::WorldToScreen(const sf::View& view, sf::Vector2f screenPos)
{
	return Framework::Instance().GetRenderWindow().mapCoordsToPixel(screenPos, view);
}
