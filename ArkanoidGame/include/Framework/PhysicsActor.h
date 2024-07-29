#pragma once
#include "Framework/Actor.h"
#include "Framework/Collider.h"
#include "Framework/ICollidable.h"

namespace Arkanoid
{
	class Collider;
	class PhysicsActor : public Actor, public ICollidable
	{
	public:
		PhysicsActor(World* owner, std::unique_ptr<Collider> collider, const sf::Vector2f& position = { 0.f,0.f }, float rotation = 0.f);
		virtual ~PhysicsActor();

		void Tick(float deltaTime) override;
		virtual void OnCollisionEnter(const ICollidable& other) override = 0;
		void SetPosition(const sf::Vector2f& newPosition) override;
		void AddPositionOffset(const sf::Vector2f& offset) override;

	protected:
		virtual void BeginPlay() override;

	private:
	};
}