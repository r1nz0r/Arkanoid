#include "Framework\PhysicsEngine.h"
#include "Game\GameSettings.h"

namespace Arkanoid
{
	std::unique_ptr<PhysicsWorld> PhysicsWorld::instance { nullptr };
	std::unique_ptr<BoundsCollider> PhysicsWorld::boundsChecker { nullptr };

	PhysicsWorld& PhysicsWorld::Instance()
	{
		if (!instance)
			instance = std::make_unique<PhysicsWorld>();

		if (!boundsChecker)
			boundsChecker = std::make_unique<BoundsCollider>();

		return *instance;
	}

	void PhysicsWorld::AddListener(ICollidable& collidable)
	{
		m_collidables.push_back(&collidable);
	}

	void PhysicsWorld::RemoveListener(const ICollidable& collidable)
	{
		m_collidables.erase(std::remove(m_collidables.begin(), m_collidables.end(), &collidable), m_collidables.end());
	}

	void PhysicsWorld::FixedUpdate(float deltaTime)
	{
		CheckCollisions();
	}

	void PhysicsWorld::CheckCollisions()
	{
		for (int i = 0; i < m_collidables.size(); ++i)
		{
			if (m_collidables[i]->GetCollider().CheckCollision(*boundsChecker))
				m_collidables[i]->OnCollisionEnter(*m_collidables[i]);

			for (int j = i + 1; j < m_collidables.size(); ++j)
			{
				if (m_collidables[i]->GetCollider().CheckCollision(m_collidables[j]->GetCollider()))
				{
					m_collidables[i]->OnCollisionEnter(*m_collidables[j]);
					m_collidables[j]->OnCollisionEnter(*m_collidables[i]);
				}
			}
		}
	}
}