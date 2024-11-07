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

bool Utils::CheckCollision(const sf::RectangleShape& shapeA, const sf::RectangleShape& shapeB)
{
    // 각각 4개의 꼭지점을 얻기
    auto pointsA = GetShapePoints(shapeA);
    auto pointsB = GetShapePoints(shapeB);
    return PolygonsIntersect(pointsA, shapeA.getTransform(), pointsB, shapeB.getTransform());
}

bool Utils::CheckCollision(const sf::Sprite& shapeA, const sf::Sprite& shapeB)
{
    auto pointsA = GetShapePoints(shapeA);
    auto pointsB = GetShapePoints(shapeB);
    return PolygonsIntersect(pointsA, shapeA.getTransform(), pointsB, shapeB.getTransform());
}

bool Utils::PointInTransformBounds(const sf::Transformable& transformalbe, const sf::FloatRect& localBounds, const sf::Vector2f& point)
{
    sf::Transform inverse = transformalbe.getInverseTransform();
    auto localPoint = inverse.transformPoint(point);
    return localBounds.contains(localPoint);
}

std::vector<sf::Vector2f> Utils::GetShapePoints(const sf::RectangleShape& shape)
{
    sf::FloatRect localBounds = shape.getLocalBounds();
    return GetRectanglePointsFromBounds(localBounds);
}

std::vector<sf::Vector2f> Utils::GetShapePoints(const sf::Sprite& sprite)
{
    sf::FloatRect localBounds = sprite.getLocalBounds();
    return GetRectanglePointsFromBounds(localBounds);
}

std::vector<sf::Vector2f> Utils::GetRectanglePointsFromBounds(const sf::FloatRect& localBounds)
{
    std::vector<sf::Vector2f> points(4);
    points[0] = sf::Vector2f(localBounds.left, localBounds.top);
    points[1] = sf::Vector2f(localBounds.left + localBounds.width, localBounds.top);
    points[2] = sf::Vector2f(localBounds.left + localBounds.width, localBounds.top + localBounds.height);
    points[3] = sf::Vector2f(localBounds.left, localBounds.top + localBounds.height);
    return points;
}

bool Utils::PolygonsIntersect(const std::vector<sf::Vector2f>& polygonA, const sf::Transform& transformA, const std::vector<sf::Vector2f>& polygonB, const sf::Transform& transformB)
{
    // 축을 만듬
    std::vector<sf::Vector2f> axes;
    int countA = (int)polygonA.size();
    for (int i = 0; i < countA; ++i)
    {
        sf::Vector2f p1 = transformA.transformPoint(polygonA[i]);
        sf::Vector2f p2 = transformA.transformPoint(polygonA[(i + 1) % countA]);
        // 방향 벡터 구하기
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f normal(-edge.y, edge.x);
        axes.push_back(Utils::GetNormal(normal));
    }

    int countB = (int)polygonB.size();
    for (int i = 0; i < countB; ++i)
    {
        sf::Vector2f p1 = transformB.transformPoint(polygonB[i]);
        sf::Vector2f p2 = transformB.transformPoint(polygonB[(i + 1) % countB]);
        sf::Vector2f edge = p2 - p1;
        sf::Vector2f normal(-edge.y, edge.x);
        axes.push_back(Utils::GetNormal(normal));
    }

    // 모든 축마다 최대 값 최소 값을 구해서 비교

    for (const auto& axis : axes)
    {
        float minA = std::numeric_limits<float>::max();
        float maxA = std::numeric_limits<float>::lowest();
        // 투영
        for (const auto& point : polygonA)
        {
            sf::Vector2f transformedPoint = transformA.transformPoint(point);
            float projection = Dot(axis, transformedPoint);
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        float minB = std::numeric_limits<float>::max();
        float maxB = std::numeric_limits<float>::lowest();
        for (const auto& point : polygonB)
        {
            sf::Vector2f transformedPoint = transformB.transformPoint(point);
            float projection = Dot(axis, transformedPoint);
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        if (maxA < minB || maxB < minA)
        {
            return false;
        }
    }
    return true;
}