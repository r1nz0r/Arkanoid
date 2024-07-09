#include "Game/GameLevel.h"
#include "Game/Paddle.h"
#include "Game/Ball.h"

namespace Arkanoid
{
	GameLevel::GameLevel(Application* owner)
		: World(owner)
		, m_ball()
		, m_paddle()
	{}

	void GameLevel::BeginPlay()
	{
		m_paddle = SpawnActor<Paddle>();
		m_ball = SpawnActor<Ball>();
	}

	void GameLevel::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			if (!m_ball.expired())
				m_ball.lock()->Detach();
	}

	void GameLevel::Tick(float deltaTime)
	{
		World::Tick(deltaTime);
		HandleInput();
	}
}