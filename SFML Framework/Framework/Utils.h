#pragma once

class Utils
{
private:
	static std::mt19937 generator;
	static const float PI;

public:
	static void Init();

	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);
	static float RandomValue();	// 0.0f ~ 1.0f
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();


	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable &obj, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);

	// Math
	static float Clamp(float value, float min, float max);
	static float Clamp01(float value);

	static float Lefp(const float& startPosition, const float& endPosition, float t, bool clamp = true);

	static sf::Color RandomColorRGB();
	static sf::Color RandomColor(bool useRandomAlpha);
	static sf::Color Lerp(const sf::Color& startColor, const sf::Color& endColor, float t, bool clamp = true);

	template<typename T>
	static sf::Vector2<T> Lerp(const sf::Vector2<T>& startPosition, const sf::Vector2<T>& destination, float time);

	static float RadianToDgree(float radian);
	static float DgreeToRadian(float degree);
	static float AngleRadian(const sf::Vector2f& directionVector);
	static float Angle(const sf::Vector2f& directionVector);


	static float SqrMagnitude(const sf::Vector2f& vec);
	static float Magnitude(const sf::Vector2f& vec);
	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	static float Dot(const sf::Vector2f& leftVector, const sf::Vector2f& rightVector);


};

