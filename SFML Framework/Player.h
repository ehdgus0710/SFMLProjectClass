#pragma once

class SceneZombieGame;
class UiHub;

struct Status
{
	int					maxHp;
	float				speed;
	int					maxAmmoCount;
	float				shootDelay;
};

class Player : public GameObject
{
protected:
	sf::Sprite			body;
	std::string			textureId;
	SceneZombieGame*	sceneGame;
	sf::FloatRect		moveableRect;

	UiHub*				uiHub;

	sf::Vector2f		direction;
	sf::Vector2f		lookDirection;
	Status				currentStatus;
	Status				defaultStatus;
	
	int					currentAmmoCount;

	int					hp;
	int					damage;

	bool				isInvulnerability;
	float				InvulnerabilityTime;
	float				currentInvulnerabilityTime;

	int					totalAmmoCount;
	float				shootTimer;
	float				maxDelayTime;
	float				defaultDelayTime;
	float				reloadTime;
	float				currentReloadTime;

	bool isReload;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetMoveableRect(const sf::FloatRect& rect) { moveableRect = rect; }
	sf::FloatRect GetLocalBounds() const  override;
	sf::FloatRect GetGlobalBounds() const override;

	void AddTotalAmmo(int count);
	void ResetStatus();

	void CreateCollider() override;

	void Shoot();

	void OnTakeDamage(int takeDamage);
	void AddHp(int hp);
	void AddDelayTime(float delay);
	void IsReload();
	void OnReload();
	void AddMaxAmmoCount(int count) { currentStatus.maxAmmoCount += count; }
	void AddMaxHp(int hp) { currentStatus.maxHp += hp; }
	void AddMoveSpeed(float moveSpeed) { currentStatus.speed += moveSpeed; }

	void SetStatus(const Status& status) { currentStatus = status; }
	Status GetCurrentStatus() { return currentStatus; }

	void IsCollision(bool isCollision);

	sf::RectangleShape& GetRectangleShape();

public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	Player(const std::string& name = "");
	~Player() = default;
};
