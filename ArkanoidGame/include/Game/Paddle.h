#pragma once
#include "Framework/PhysicsActor.h"

namespace Arkanoid
{
	class Paddle : public PhysicsActor
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
		virtual void OnCollisionEnter(const Collider& other) override;

	private:
		EMoveDirection m_direction;
		float m_speed;
		sf::Vector2f m_velocity;
		sf::Vector2f m_moveInput;

		void HandleInput();
		void ClampPosition();
		void ConsumeInput(float deltaTime);
	};
}