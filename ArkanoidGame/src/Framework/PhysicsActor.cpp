#include "Framework/PhysicsActor.h"
#include "Framework/Collider.h"
#include "Framework/PhysicsEngine.h"
#include <memory>

namespace Arkanoid
{
	PhysicsActor::PhysicsActor(World* owner, std::unique_ptr<Collider> collider, const sf::Vector2f& position, float rotation)
		: Actor(owner, position, rotation)
		, ICollidable(this)
	{
		m_collider = std::move(collider);
		PhysicsEngine::Instance().AddListener(*this);
	}

	PhysicsActor::~PhysicsActor()
	{
		PhysicsEngine::Instance().RemoveListener(*this);
	}

	void PhysicsActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
	}

	void PhysicsActor::SetPosition(const sf::Vector2f& newPosition)
	{
		Actor::SetPosition(newPosition);
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