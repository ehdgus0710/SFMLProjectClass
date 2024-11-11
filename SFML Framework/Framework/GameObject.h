#pragma once

class Collider;

class GameObject
{
protected:
	std::string name;
	
	bool active = true;

	sf::Vector2f position;
	sf::Vector2f scale;
	float rotation;

	Origins originPreset;
	sf::Vector2f origin;

	Collider* collider;

public:

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& scale) { this->scale = scale; }

	virtual float GetRotation() const{ return rotation; }
	virtual void SetRotation(float angle) { rotation = angle; }

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

	virtual void CreateCollider();
	Collider* GetCollider() { return collider; }

	virtual sf::FloatRect GetLocalBounds() const { return { 0.f , 0.f  , 0.f , 0.f }; }
	virtual sf::FloatRect GetGlobalBounds() const { return { 0.f , 0.f  , 0.f , 0.f }; }

	virtual void OnLocalize(Languages lange) {}

public:

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void LateUpdate(float dt) {}
	virtual void FixedUpdate(float dt) {}
	virtual void Draw(sf::RenderWindow& window);

public:
	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;

	GameObject(const std::string& name = "");
	virtual ~GameObject();
};

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b) const
	{
		if (a->sortingLayer != b->sortingLayer)
			return a->sortingLayer > b->sortingLayer;
		return a->sortingOrder > b->sortingOrder;
	}
};

