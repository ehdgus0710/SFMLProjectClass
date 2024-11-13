#pragma once

class AniPlayer : public GameObject
{
protected:
	sf::Sprite	body;
	Animator	animator;

	AnimationClip idle;

	AnimationClip run;
	AnimationClip jump;

	bool isJump;

	sf::Vector2f velocity;
	float speed = 500.f;
	float gravity = 300.f;
	bool isGrounded = true;
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Test();

public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	AniPlayer(const std::string& name = "");
	~AniPlayer() = default;

};
