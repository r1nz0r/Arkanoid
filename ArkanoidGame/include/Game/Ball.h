#pragma once
#include "Framework/Actor.h"
#include "Framework/Collider.h"

namespace Arkanoid
{
	class World;
	class Ball : public Actor
	{
	public:
		enum class BounceDirectionBitMask : uint8_t
		{
			None = 0,
			Up = 1 << 0,
			Down = 1 << 1,
			Right = 1 << 2,
			Left = 1 << 3,

			Horizontal = Right | Left,
			Vertical = Up | Down,
			Default = None
		};

		Ball(World* owner);
		~Ball() = default;
		void Tick(float deltaTime) override;
		void BeginPlay() override;
		void SetVelocity(const sf::Vector2f& velocity);
		void SetPosition(const sf::Vector2f& newPosition) override;
		void AddPositionOffset(const sf::Vector2f& offset) override;		
		void Detach();
		bool IsAttachedToPaddle() const { return m_isAttached; }

	private:
		bool CheckBounceDirection(BounceDirectionBitMask flags);
		void SetBounceDirection(BounceDirectionBitMask flag);
		void UpdateBounceDirection();
		void DoCollisionTests();
		void OnPaddleCollision(const Rectangle& other);
		void OnVerticalBoundsCollision();
		void OnHorizontalBoundsCollision();
		float GetPaddleHitNormalizedPoint(const Rectangle& paddle) const;
		float GetPaddleBounceAngle(const Rectangle& paddle) const;

		sf::Vector2f m_velocity;
		float m_speed;
		uint8_t m_bounceDirection;
		bool m_isAttached;
		Circle m_collider;
	};
}