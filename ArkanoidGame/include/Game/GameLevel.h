#pragma once
#include "Framework/World.h"

namespace Arkanoid
{
	class Ball;
	class Paddle;
	class GameLevel final: public World
	{
	public:
		GameLevel(Application* owner);
		~GameLevel() = default;

		virtual void BeginPlay() override;
		void HandleInput();
		std::weak_ptr<Paddle> GetPaddle() const { return m_paddle; }
		inline sf::Vector2u GetWindowSize() const { return m_owner->GetWindowSize(); };

	private:
		virtual void Tick(float deltaTime);
		std::weak_ptr<Ball> m_ball;
		std::weak_ptr<Paddle> m_paddle;
	};
}