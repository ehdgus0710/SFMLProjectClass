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
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawQueue;

	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		drawQueue.push(obj);
	}

	const sf::View& saveView = window.getView();
	window.setView(cameraView);

	while (!drawQueue.empty())
	{
		GameObject* obj = drawQueue.top();
		obj->Draw(window);
		drawQueue.pop();
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
	return Framework::Instance().GetRenderWindow().mapPixelToCoords(screenPos);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f screenPos)
{
	return Framework::Instance().GetRenderWindow().mapCoordsToPixel(screenPos);
}
