#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	namespace Math
	{
		constexpr double DOUBLE_TOLERANCE = 1e-7;
		constexpr float PI = 3.1415f;
		constexpr float STRAIGHT_ANGLE = 180.f;

		bool IsNearlyEqual(const double lhs, const double rhs);		
		float GetRadiansFromDegrees(const float degrees);
		float GetRandomFloat(const float minValue, const float maxValue);
		bool GetRandomBool();

		template<typename T>
		float GetVectorLength(const sf::Vector2<T>& vector)
		{
			return std::sqrt(vector.x * vector.x + vector.y * vector.y);
		}

		template<typename T>
		sf::Vector2<T> GetNormalizedVector(const sf::Vector2<T>& baseVector)
		{
			const float length = GetVectorLength(baseVector);
			return sf::Vector2<T> { baseVector.x / length, baseVector.y / length };
		}

		template<typename T>
		sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vector, float factor)
		{
			vector.x *= factor;
			vector.y *= factor;
			return vector;
		}
	}
}