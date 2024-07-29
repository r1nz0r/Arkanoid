#pragma once

#include "SFML/Graphics.hpp"
#include "Framework/Noncopyable.h"

namespace Arkanoid
{
	class World;
	class Application : private NonCopyable
	{
	public:
		//friend std::default_delete<Application>;
		static Application& Instance();
		void Run();
		inline sf::Vector2u GetWindowSize() const { return m_renderWindow.getSize(); };

		//sf::RenderWindow& GetWindow() { return m_renderWindow; }
		//const sf::RenderWindow& GetWindow() const { return m_renderWindow; }

	private:
		Application();
		~Application();

		void Tick(float deltaTime);
		void Render();
		void RenderInternal();

		static Application* instance;
		sf::RenderWindow m_renderWindow;
		float m_targetFramerate;

		sf::Clock m_gameClock;
		float m_deltaTime;

		sf::Clock m_cleanClock;
		float m_cleanInterval;

		std::unique_ptr<World> m_world;
	};
}