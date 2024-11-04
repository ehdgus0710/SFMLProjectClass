#pragma once

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	sf::RenderWindow window;

	sf::Clock clock;
	float timeScale = 1.f;

	float time = 0.f;
	float deltaTime = 0.f;
	float realTime = 0.f;
	float realDeltaTime = 0.f;

public:
	float GetTime() const { return time; }
	float GetDeltaTime() const { return deltaTime; }
	float GetRealTime() const { return realTime; }
	float GetRealDeltaTime() const { return realDeltaTime; }

	void SetTimeScale(float newTimeScale) { timeScale = newTimeScale; }
	float GetTimeScale() const { return timeScale; }

	sf::RenderWindow& GetRenderWindow() { return window; }
	sf::Vector2u GetWindowSize() { return window.getSize(); }
	sf::Vector2f GetWindowSizeFloat() { return (sf::Vector2f)window.getSize(); }
	sf::FloatRect GetWindowBounds()
	{
		auto size = GetWindowSizeFloat();
		return sf::FloatRect(0.f, 0.f, size.x, size.y);
	}

public:

	virtual void Init(int width, int height, const std::string& name);
	virtual void Do();
	virtual void Release();

protected:
	Framework() = default;
	virtual ~Framework() = default;

	Framework(const Framework& other) = delete;
	Framework& operator=(const Framework& other) = delete;
};

#define FRAMEWORK (Framework::Instance())