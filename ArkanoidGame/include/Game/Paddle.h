#pragma once
#include "Framework/Actor.h"
#include "Framework/Collider.h"

namespace Arkanoid
{
	class Paddle : public Actor
	{
	public:
		enum class EMoveDirection
		{
			Up,
			Down,
			None
		};

		Paddle(World* owner);
		~Paddle() = default;

		void Tick(float deltaTime) override;
		void BeginPlay() override;
		void SetVelocity(const sf::Vector2f& velocity);
		void SetPosition(const sf::Vector2f& newPosition) override;
		void AddPositionOffset(const sf::Vector2f& offset) override;
		const Rectangle& GetCollider() const { return m_collider; }

	private:
		EMoveDirection m_direction;
		float m_speed;
		sf::Vector2f m_velocity;
		sf::Vector2f m_moveInput;
		Rectangle m_collider;

		void HandleInput();
		void ClampPosition();
		void ConsumeInput(float deltaTime);
	};
}