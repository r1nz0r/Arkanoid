#pragma once
#include <memory>
#include <vector>
#include "Framework/Noncopyable.h"
#include "Framework/ICollidable.h"
#include "Framework/Collider.h"

namespace Arkanoid
{
	class PhysicsEngine : private NonCopyable
	{
	public:
		static PhysicsEngine& Instance();
		void AddListener(ICollidable& collidable);
		void RemoveListener(const ICollidable& collidable);
		void FixedUpdate(float deltaTime);
		BoundsCollider::ECollisionType GetBoundsCollisionType() const { return boundsChecker->GetCollisionType(); }
	private:
		void CheckCollisions();

		static std::unique_ptr<PhysicsEngine> instance;
		static std::unique_ptr<BoundsCollider> boundsChecker;
		std::vector<ICollidable*> m_collidables;
	};
}