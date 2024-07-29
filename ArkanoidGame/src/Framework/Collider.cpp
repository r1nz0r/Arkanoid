#include <SFMl/Graphics.hpp>
#include "Framework/Collider.h"
#include "Game/GameSettings.h"
#include "Game/Ball.h"

namespace Arkanoid
{
	Collider::Collider(const sf::Vector2f& position)
		: m_position(position)
	{}

	Circle::Circle(const sf::Vector2f& position, float radius)
		: Collider(position)
		, m_radius(radius)
	{}

	bool Circle::CheckCollision(const Collider& other) const
	{
		return other.CheckCollision(*this);
	}

	bool Circle::CheckCollision(const Rectangle& other) const
	{
		auto rhsPosition = other.GetPosition();
		auto lhsPosition = GetPosition();

		const float rectangleX = std::max(
			rhsPosition.x, std::min(lhsPosition.x, rhsPosition.x + other.GetSize().x));
		const float dx = lhsPosition.x - rectangleX;

		const float rectangleY = std::max(
			rhsPosition.y, std::min(lhsPosition.y, rhsPosition.y + other.GetSize().y));
		const float dy = lhsPosition.y - rectangleY;

		return (dx * dx + dy * dy) < (GetRadius() * GetRadius());
	}

	bool Circle::CheckCollision(const Circle& other) const
	{
		float dx = GetPosition().x - other.GetPosition().x;
		float dy = GetPosition().y - other.GetPosition().y;
		float distSumSqr = dx * dx + dy * dy;
		float radiusSumSqr = (GetRadius() + other.GetRadius()) * (GetRadius() + other.GetRadius());

		return distSumSqr <= radiusSumSqr;
	}

	Rectangle::Rectangle(const sf::Vector2f& position, const sf::Vector2f& size)
		: Collider(position)
		, m_size(size)
	{}

	bool Rectangle::CheckCollision(const Collider& other) const
	{
		return other.CheckCollision(*this);
	}

	bool Rectangle::CheckCollision(const Rectangle& other) const
	{
		sf::FloatRect thisRect(GetPosition(), GetSize());
		sf::FloatRect otherRect(other.GetPosition(), other.GetSize());
		return thisRect.intersects(otherRect);
	}

	bool Rectangle::CheckCollision(const Circle& other) const
	{
		return other.CheckCollision(*this);
	}

	BoundsCollider::BoundsCollider(const sf::Vector2f& position, const sf::Vector2f& size)
		: Collider()
		, m_collisionType(ECollisionType::None)
	{}

	bool BoundsCollider::CheckCollision(const Collider& other) const
	{
		return other.CheckCollision(*this);
	}

	bool BoundsCollider::CheckCollision(const Rectangle& other) const
	{
		m_collisionType = ECollisionType::None;

		auto position = other.GetPosition();
		auto size = other.GetSize();

		if (position.x + size.x >= SCREEN_WIDTH ||
			position.x <= 0)
			m_collisionType = ECollisionType::Horizontal;
		else if (position.y + size.y >= SCREEN_HEIGHT ||
			position.y <= 0)
			m_collisionType = ECollisionType::Vertical;

		return m_collisionType != ECollisionType::None;
	}

	bool BoundsCollider::CheckCollision(const Circle& other) const
	{
		m_collisionType = ECollisionType::None;

		auto position = other.GetPosition();
		auto radius = other.GetRadius();

		if (position.y + radius >= SCREEN_HEIGHT ||
			position.y - radius <= 0)
			m_collisionType = ECollisionType::Vertical;
		else if (position.x + radius >= SCREEN_WIDTH ||
			position.x - radius <= 0)
			m_collisionType = ECollisionType::Horizontal;

		return m_collisionType != ECollisionType::None;
	}
}