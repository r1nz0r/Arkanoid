#include <SFMl/Graphics.hpp>
#include "Framework/Collider.h"
#include "Game/GameSettings.h"
#include "Game/Ball.h"

namespace Arkanoid
{
	Collider::Collider(const sf::Vector2f& position)
		: m_position(position)
	{}

	bool Collider::CheckCollision(const Collider* lhs, const Collider* rhs)
	{
		if (!lhs || !rhs)
			return false;	

		const Circle* col1 = dynamic_cast<const Circle*>(lhs);
		const Rectangle* col2 = dynamic_cast<const Rectangle*>(rhs);

		if (col1 && col2)
			return Collider::CheckCircleToRectCollision(*col1, *col2);

		col1 = dynamic_cast<const Circle*>(lhs);
		col2 = dynamic_cast<const Rectangle*>(rhs);

		if (col1 && col2)
			return Collider::CheckCircleToRectCollision(*col1, *col2);

		return false;
	}

	bool Collider::CheckBoundsCollision(const Circle& object)
	{
		auto position = object.GetPosition();
		auto radius = object.GetRadius();

		if (position.x - radius <= 0 ||
			position.x + radius >= SCREEN_WIDTH ||
			position.y - radius <= 0 ||
			position.y + radius >= SCREEN_HEIGHT)
		{
			return true;
		}

		return false;
	}

	bool Collider::CheckBoundsCollision(const Rectangle& object)
	{
		auto position = object.GetPosition();
		auto size = object.GetSize();

		if (position.x <= 0 ||
			position.x + size.x >= SCREEN_WIDTH ||
			position.y <= 0 ||
			position.y + size.y >= SCREEN_HEIGHT)
		{
			return true;
		}

		return false;
	}

	bool Collider::CheckHorizontalBoundsCollision(const Collider* const object)
	{
		const Circle* circle = dynamic_cast<const Circle*>(object);

		if (circle)
		{
			auto position = circle->GetPosition();
			auto radius = circle->GetRadius();

			if (position.x + radius >= SCREEN_WIDTH ||
				position.x - radius <= 0)
				return true;
		}
		
		const Rectangle* rect = dynamic_cast<const Rectangle*>(object);

		if (rect)
		{
			auto position = rect->GetPosition();
			auto size = rect->GetSize();

			if (position.x + size.x >= SCREEN_WIDTH ||
				position.x <= 0)
				return true;
		}

		return false;
	}

	bool Collider::CheckVerticalBoundsCollision(const Collider* const object)
	{
		const Circle* circle = dynamic_cast<const Circle*>(object);

		if (circle)
		{
			auto position = circle->GetPosition();
			auto radius = circle->GetRadius();

			if (position.y + radius >= SCREEN_HEIGHT ||
				position.y - radius <= 0)
				return true;
		}

		const Rectangle* rect = dynamic_cast<const Rectangle*>(object);

		if (rect)
		{
			auto position = rect->GetPosition();
			auto size = rect->GetSize();

			if (position.y + size.x >= SCREEN_HEIGHT ||
				position.y <= 0)
				return true;
		}

		return false;
	}

	bool Collider::CheckCircleToRectCollision(const Circle& lhs, const Rectangle& rhs)
	{
		auto rhsPosition = rhs.GetPosition();
		auto lhsPosition = lhs.GetPosition();

		const float rectangleX = std::max(
			rhsPosition.x, std::min(lhsPosition.x, rhsPosition.x + rhs.GetSize().x));
		const float dx = lhsPosition.x - rectangleX;

		const float rectangleY = std::max(
			rhsPosition.y, std::min(lhsPosition.y, rhsPosition.y + rhs.GetSize().y));
		const float dy = lhsPosition.y - rectangleY;

		return (dx * dx + dy * dy) < (lhs.GetRadius() * lhs.GetRadius());
	}

	Circle::Circle(const sf::Vector2f& position, float radius)
		: Collider(position)
		, m_radius(radius)
	{
	}

	Rectangle::Rectangle(const sf::Vector2f& position, const sf::Vector2f& size)
		: Collider(position)
		, m_size(size)
	{
	}
}