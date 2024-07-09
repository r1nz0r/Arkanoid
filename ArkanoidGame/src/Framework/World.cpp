#include "Framework/World.h"
#include "Framework/Actor.h"
#include "Framework/Core.h"
#include "Game/Paddle.h"
#include "Game/Ball.h"

namespace Arkanoid
{
	World::World(Application* owner)
		: m_owner(owner)
		, m_pendingActors()
		, m_actors()
	{
	}
	
	void World::BeginPlay()
	{
		m_paddle = SpawnActor<Paddle>();
		m_ball = SpawnActor<Ball>();
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

		HandleInput();
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
			if (iter->get()->IsPendingDestroy())
				iter = m_actors.erase(iter);
			else
				++iter;
		}
	}

	void World::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			if (!m_ball.expired())
				m_ball.lock()->Detach();
	}
}
