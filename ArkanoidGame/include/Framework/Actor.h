#pragma once
#include "Framework/Entity.h"
#include "SFML/Graphics.hpp"

namespace Arkanoid
{
	class World;
	class Actor : public Entity
	{
	public:
		Actor(World* owner, const sf::Vector2f& position = { 0.f,0.f }, float rotation = 0.f);
		virtual ~Actor() = default;

		void Render(sf::RenderWindow& window) const;
		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		inline sf::Vector2f GetPosition() const { return m_shape->getPosition(); } 
		virtual void SetPosition(const sf::Vector2f& newPosition) { m_shape->setPosition(newPosition); }
		inline float GetRotation() const { return m_shape->getRotation(); } // Returns rotation in degrees
		void SetRotation(float newRotation) { m_shape->setRotation(newRotation); }
		inline sf::FloatRect GetGlobalBounds() const { return m_shape->getGlobalBounds(); };
		virtual void AddPositionOffset(const sf::Vector2f& offset);
		void AddRotationOffset(float offset);
		void CenterPivot();

	protected:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		World* m_owner;
		std::unique_ptr<sf::Shape> m_shape;
	private:
		bool m_isBeganPlay;
	};
}