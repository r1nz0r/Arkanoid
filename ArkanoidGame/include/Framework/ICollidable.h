#pragma once
#include <memory>
#include "Framework/Collider.h"
#include "Framework/Entity.h"

namespace Arkanoid
{
	class ICollidable
	{
	public:
		virtual ~ICollidable() = default;
		virtual void OnCollisionEnter(const ICollidable& other) = 0;
		const Entity* GetOwner() const { return m_ownerActor; }
		virtual Collider& GetCollider() const { return *m_collider; }

	protected:
		std::unique_ptr<Collider> m_collider { nullptr };
		ICollidable(Entity* owner) : m_ownerActor(owner) {};

	private:
		Entity* m_ownerActor;
	};
}