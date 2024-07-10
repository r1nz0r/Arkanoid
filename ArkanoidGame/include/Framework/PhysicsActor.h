#pragma once
#include "Framework/Actor.h"

namespace Arkanoid
{
	class Collider;
	class PhysicsActor : public Actor
	{
	public:
		PhysicsActor(World* owner, Collider* collider = nullptr, const sf::Vector2f& position = { 0.f,0.f }, float rotation = 0.f);
		virtual ~PhysicsActor() = default;

		void Tick(float deltaTime) override;
		bool CheckCollision(const PhysicsActor* other) const;
		Collider* GetCollider() const { return m_collider.get(); }
		virtual void OnCollisionEnter(const Collider& other) = 0;
		void SetPosition(const sf::Vector2f& newPosition) override;
		void AddPositionOffset(const sf::Vector2f& offset) override;

	protected:
		virtual void BeginPlay() override;
		std::unique_ptr<Collider> m_collider;
	};
}