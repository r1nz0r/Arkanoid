#include "Framework\PhysicsEngine.h"
#include "Game\GameSettings.h"

namespace Arkanoid
{
	std::unique_ptr<PhysicsEngine> PhysicsEngine::instance{ nullptr };
	std::unique_ptr<BoundsCollider> PhysicsEngine::boundsChecker{ nullptr };

	PhysicsEngine& PhysicsEngine::Instance()
	{
		if (!instance)
			instance = std::make_unique<PhysicsEngine>();

		if (!boundsChecker)
			boundsChecker = std::make_unique<BoundsCollider>();

		return *instance;
	}

	void PhysicsEngine::AddListener(ICollidable& collidable)
	{
		m_collidables.push_back(&collidable);
	}

	void PhysicsEngine::RemoveListener(const ICollidable& collidable)
	{
		m_collidables.erase(std::remove(m_collidables.begin(), m_collidables.end(), &collidable), m_collidables.end());
	}

	void PhysicsEngine::FixedUpdate(float deltaTime)
	{
		CheckCollisions();
	}

	void PhysicsEngine::CheckCollisions()
	{
		for (int i = 0; i < m_collidables.size(); ++i)
		{
			if (m_collidables[i]->GetOwner()->IsPendingToDestroy())
				continue;

			if (m_collidables[i]->GetCollider().CheckCollision(*boundsChecker))
				m_collidables[i]->OnCollisionEnter(*m_collidables[i]);

			for (int j = i + 1; j < m_collidables.size(); ++j)
			{
				if (m_collidables[j]->GetOwner()->IsPendingToDestroy())
					continue;

				if (m_collidables[i]->GetCollider().CheckCollision(m_collidables[j]->GetCollider()))
				{
					m_collidables[i]->OnCollisionEnter(*m_collidables[j]);
					m_collidables[j]->OnCollisionEnter(*m_collidables[i]);
				}
			}
		}
	}
}
