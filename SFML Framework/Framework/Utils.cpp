#define _USE_MATH_DEFINES

#include "stdafx.h"
#include "Utils.h"
#include <cmath>

std::mt19937 Utils::generator;
const float Utils::PI = acosf(-1.f);

void Utils::Init()
{
    std::random_device rd;
    generator.seed(rd());
}

int Utils::RandomRange(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator);
}

float Utils::RandomRange(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
}

float Utils::RandomValue()
{
    return RandomRange(0.f, 1.f);
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
    float angle = RandomRange(0.f, 2.f * PI);
    return sf::Vector2f(std::cosf(angle), std::sinf(angle));
}

sf::Vector2f Utils::RandomInUnitCircle()
{
    return RandomOnUnitCircle() * RandomValue();
}

float Utils::Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

float Utils::Clamp01(float value)
{
    return Clamp(value, 0.f, 1.f);
}

float Utils::Lefp(const float& startPosition, const float& endPosition, float t, bool clamp)
{
    if (clamp)
        t = Clamp(t, 0.f, 1.f);
    return startPosition + (startPosition - endPosition) * t;
}

sf::Color Utils::RandomColorRGB()
{
    return RandomColor(false);
}

sf::Color Utils::RandomColor(bool useRandomAlpha)
{
	return sf::Color
    (
		{ (sf::Uint8)RandomRange(0, 255)
        , (sf::Uint8)RandomRange(0, 255)
        , (sf::Uint8)RandomRange(0, 255)
        , useRandomAlpha ? (sf::Uint8)RandomRange(0, 255) : (sf::Uint8)255}
    );
}

sf::Color Utils::Lerp(const sf::Color& startColor, const sf::Color& endColor, float t, bool clamp)
{
    if (clamp)
        t = Clamp(t, 0.f, 1.f);

	return sf::Color(
		{
			(sf::Uint8)Lefp(startColor.r, endColor.r, t, clamp)
			, (sf::Uint8)Lefp(startColor.g, endColor.g, t, clamp)
			, (sf::Uint8)Lefp(startColor.b, endColor.b, t, clamp)
			, (sf::Uint8)Lefp(startColor.a, endColor.a, t, clamp)
		});
}

float Utils::RadianToDgree(float radian)
{
    return radian * (180.f / PI);
}

float Utils::DgreeToRadian(float degree)
{
    return degree * (PI / 180.f);
}

float Utils::AngleRadian(const sf::Vector2f& directionVector)
{
    return std::atan2(directionVector.y, directionVector.x);
}

float Utils::Angle(const sf::Vector2f& directionVector)
{
    return RadianToDgree(AngleRadian(directionVector));
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
    return std::sqrtf(SqrMagnitude(vec));
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{
    float mag = Magnitude(vec);
    if (mag == 0)
        return vec;
    return vec / mag;
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return Magnitude(p2 - p1);
}

float Utils::Dot(const sf::Vector2f& leftVector, const sf::Vector2f& rightVector)
{
    return leftVector.x * rightVector.x + leftVector.y * rightVector.y;
}

template<typename T>
inline sf::Vector2<T> Utils::Lerp(const sf::Vector2<T>& startPosition, const sf::Vector2<T>& destination, float time)
{
    time = (time > 1.0f) ? 1.0f : ((time < 0.0f) ? 0.0f : time);
    return startPosition * (1.0f - time) + destination * time;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect rect)
{
    sf::Vector2f newOrigin(rect.width, rect.height);
    newOrigin.x *= ((int)preset % 3) * 0.5f;
    newOrigin.y *= ((int)preset / 3) * 0.5f;
    obj.setOrigin(newOrigin);
    return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}
