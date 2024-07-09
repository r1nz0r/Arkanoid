#pragma once
#include "SFML/Graphics.hpp"

namespace Arkanoid
{
	class Circle;
	class Rectangle;
	class Collider
	{
	public:
		Collider(const sf::Vector2f& position = {0.f,0.f});
		sf::Vector2f GetPosition() const { return m_position; }
		void SetPosition(const sf::Vector2f position) { m_position = position; }

		static bool CheckCollision(const Circle& object, const Rectangle& other);
		static bool CheckBoundsCollision(const Circle& object);
		static bool CheckBoundsCollision(const Rectangle& object);
		static bool CheckHorizontalBoundsCollision(const Circle& object);
		static bool CheckVerticalBoundsCollision(const Circle& object);

	private:
		sf::Vector2f m_position;
	};

	class Circle : public Collider
	{
	public:
		Circle(const sf::Vector2f& position = {0.f, 0.f}, float radius = 0.f);
		float GetRadius() const { return m_radius; }

	private:
		float m_radius;
	};

	class Rectangle : public Collider
	{
	public:
		Rectangle(const sf::Vector2f& position = {0.f, 0.f}, const sf::Vector2f& size = {0.f, 0.f});
		sf::Vector2f GetSize() const { return m_size; }

	private:
		sf::Vector2f m_size;
	};
}
