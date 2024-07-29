#pragma once
#include "SFML/Graphics.hpp"

namespace Arkanoid
{
	class Circle;
	class Rectangle;
	class Collider
	{
	public:
		Collider(const sf::Vector2f& position = { 0.f,0.f });
		virtual ~Collider() = default;
		sf::Vector2f GetPosition() const { return m_position; }
		void SetPosition(const sf::Vector2f position) { m_position = position; }

		virtual bool CheckCollision(const Collider& other) const = 0;
		virtual bool CheckCollision(const Rectangle& other) const = 0;
		virtual bool CheckCollision(const Circle& other) const = 0;

	private:
		sf::Vector2f m_position;
	};

	class Circle : public Collider
	{
	public:
		Circle(const sf::Vector2f& position = { 0.f, 0.f }, float radius = 0.f);
		float GetRadius() const { return m_radius; }

		virtual bool CheckCollision(const Collider& other) const override;
		virtual bool CheckCollision(const Rectangle& other) const override;
		virtual bool CheckCollision(const Circle& other) const override;

	private:
		float m_radius;
	};

	class Rectangle : public Collider
	{
	public:
		Rectangle(const sf::Vector2f& position = { 0.f, 0.f }, const sf::Vector2f& size = { 0.f, 0.f });

		const sf::Vector2f& GetSize() const { return m_size; }
		virtual bool CheckCollision(const Collider& other) const override;
		virtual bool CheckCollision(const Rectangle& other) const override;
		virtual bool CheckCollision(const Circle& other) const override;

	protected:
		sf::Vector2f m_size;
	};

	class BoundsCollider : public Collider
	{
	public:
		enum class ECollisionType
		{
			None,
			Horizontal,
			Vertical
		};

		BoundsCollider(const sf::Vector2f& position = { 0.f, 0.f }, const sf::Vector2f& size = { 0.f, 0.f });

		ECollisionType GetCollisionType() const { return m_collisionType; }
		virtual bool CheckCollision(const Collider& other) const override;
		virtual bool CheckCollision(const Rectangle& other) const override;
		virtual bool CheckCollision(const Circle& other) const override;

	private:
		mutable ECollisionType m_collisionType;
	};
}