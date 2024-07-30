#pragma once
#include "Framework/PhysicsActor.h"

namespace Arkanoid
{
	class Block : public PhysicsActor
	{
	public:
		Block(World* owner);
		~Block() = default;

		void Tick(float deltaTime) override;
		void BeginPlay() override;
		virtual void OnCollisionEnter(const ICollidable& other) override;
		void SetPosition(const sf::Vector2f& newPosition) override;
	};
}