#pragma once
class Scene
{
protected:
	std::list<GameObject*> gameObjects;

	std::list<GameObject*> addGameObjects;
	std::list<GameObject*> removeGameObjects;

	sf::View cameraView;
	sf::View uiView;

public:
	const SceneIds id;


	template<typename T>
	T* AddGo(T* obj)
	{
		addGameObjects.push_back(obj);
		return obj;
	}

	virtual void RemoveGo(GameObject* obj);
	virtual GameObject* FindGo(const std::string& name);
	virtual int FindGoAll(const std::string& name, std::list<GameObject*>& list);

	void ApplyAddGo();
	void ApplyRemoveGO();

	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos);
	sf::Vector2i WorldToScreen(sf::Vector2f screenPos);

	sf::Vector2f ScreenToUI(sf::Vector2i screenPos);
	sf::Vector2i UIToScreen(sf::Vector2f screenPos);
	sf::Vector2f ScreenToWorld(const sf::View& view,  sf::Vector2i screenPos);
	sf::Vector2i WorldToScreen(const sf::View& view,  sf::Vector2f screenPos);

public:
	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);

	virtual void OnPreDraw();
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnPostDraw();
	virtual void OnLocalize(Languages langugage);
		
public:
	Scene(SceneIds id);
	virtual ~Scene() = default;


};

