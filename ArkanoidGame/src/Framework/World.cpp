#include "Framework/World.h"
#include "Framework/Actor.h"
#include "Framework/Core.h"

namespace Arkanoid
{
	World::World(Application* owner)
		: m_owner(owner)
		, m_pendingActors()
		, m_actors()
	{
	}
	
	void World::BeginPlay()
	{}

	void World::TickInternal(float deltaTime)
	{
		if (IsPendingToDestroy())
			return;

		Tick(deltaTime);
	}

	void World::Tick(float deltaTime)
	{
		for (auto iter = m_pendingActors.begin(); iter != m_pendingActors.end();)
		{
			m_actors.push_back(*iter);
			iter++->get()->BeginPlayInternal();
		}
		
		m_pendingActors.clear();

		for (auto iter = m_actors.begin(); iter != m_actors.end(); ++iter)
			iter->get()->TickInternal(deltaTime);
	}

	void World::Render(sf::RenderWindow& window) const
	{
		for (const auto actor : m_actors)
		{
			actor->Render(window);
		}
	}

	void World::Clean()
	{
		for (auto iter = m_actors.begin(); iter != m_actors.end();)
		{			
			if (iter->get()->IsPendingToDestroy())
				iter = m_actors.erase(iter);
			else
				++iter;
		}
	}	
}
