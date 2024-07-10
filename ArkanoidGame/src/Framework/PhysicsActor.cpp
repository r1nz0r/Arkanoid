#include "Framework/PhysicsActor.h"
#include "Framework/Collider.h"
#include <memory>

namespace Arkanoid
{
	PhysicsActor::PhysicsActor(World* owner, Collider* collider, const sf::Vector2f& position, float rotation)
		: Actor(owner, position, rotation)
		, m_collider(collider)
	{}

	void PhysicsActor::Tick(float deltaTime)
	{
	}

	bool PhysicsActor::CheckCollision(const PhysicsActor* other) const
	{
		if (!other)
			return false;

		auto otherCollider = other->GetCollider();
				
		return Collider::CheckCollision(m_collider.get(), otherCollider);
	}

	void PhysicsActor::SetPosition(const sf::Vector2f& newPosition)
	{
		Actor::SetPosition(newPosition);

		if (m_collider)
		{
			auto shapeBounds = m_shape->getLocalBounds();

			if (dynamic_cast<Rectangle*>(m_collider.get()) != nullptr)
				m_collider->SetPosition(GetPosition() - sf::Vector2f(shapeBounds.width / 2, shapeBounds.height / 2));
			else
				m_collider->SetPosition(GetPosition());
		}
	}

	void PhysicsActor::AddPositionOffset(const sf::Vector2f& offset)
	{
		Actor::AddPositionOffset(offset);

		if (m_collider)
			m_collider->SetPosition(m_collider->GetPosition() + offset);
	}

	void PhysicsActor::BeginPlay()
	{
		Actor::BeginPlay();
		SetPosition(GetPosition());
	}
}