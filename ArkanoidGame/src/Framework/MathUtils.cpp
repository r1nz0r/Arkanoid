#include "Framework/MathUtils.h"

namespace Arkanoid
{
	namespace Math
	{	

		bool IsNearlyEqual(const double numOne, const double numTwo)
		{
			return (std::fabs(numOne - numTwo) <= DOUBLE_TOLERANCE);
		}

		float GetRadiansFromDegrees(const float degrees)
		{
			return degrees * PI / STRAIGHT_ANGLE;
		}

		float GetRandomFloat(const float minValue, const float maxValue)
		{
			return minValue + rand() / static_cast<float>((RAND_MAX)) * (maxValue - minValue);
		}
		bool GetRandomBool()
		{
			return static_cast<bool>(rand() % 2);
		}
	}
}