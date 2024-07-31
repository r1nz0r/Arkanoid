#include "Game/GameLevel.h"
#include "Game/Paddle.h"
#include "Game/Ball.h"
#include "Game/Block.h"

namespace Arkanoid
{
	GameLevel::GameLevel(Application* owner)
		: World(owner)
		, m_ball()
		, m_paddle()
	{}

	void GameLevel::BeginPlay()
	{
		World::BeginPlay();
		m_paddle = SpawnActor<Paddle>();
		m_ball = SpawnActor<Ball>();

		for (int i = 1; i < 9; ++i)
		{
			auto block = SpawnActor<Block>();
			block.lock()->SetPosition({ 80.f * (float)i, 50.f });
		}

		for (int i = 2; i < 7; ++i)
		{
			auto block = SpawnActor<Block>();
			block.lock()->SetPosition({ 80.f * (float)i, 125.f });
		}

		for (int i = 1; i < 9; ++i)
		{
			auto block = SpawnActor<Block>();
			block.lock()->SetPosition({ 80.f * (float)i, 170.f });
		}

		for (int i = 4; i < 8; ++i)
		{
			auto block = SpawnActor<Block>();
			block.lock()->SetPosition({ 80.f * (float)i, 240.f });
		}

		for (int i = 1; i < 9; ++i)
		{
			auto block = SpawnActor<Block>();
			block.lock()->SetPosition({ 80.f * (float)i, 280.f });
		}

		for (int i = 1; i < 9; ++i)
		{
			auto block = SpawnActor<Block>();
			block.lock()->SetPosition({ 80.f * (float)i, 320.f });
		}
	}

	void GameLevel::HandleInput()
	{
		//Should be moved to smwhere else, i.e. in future PlayerController.
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
