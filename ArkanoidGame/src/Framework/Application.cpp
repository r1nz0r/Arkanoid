#include "Framework/Application.h"
#include "Framework/Core.h"
#include "Framework/PhysicsEngine.h"
#include "Game/GameLevel.h"
#include "Game/GameSettings.h"

namespace Arkanoid
{	
	Application::Application()
		: m_renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_NAME, sf::Style::Close | sf::Style::Titlebar)
		, m_targetFramerate(TARGET_FRAMERATE)
		, m_deltaTime(0.f)
		, m_cleanClock()
		, m_gameClock()		
		, m_cleanInterval(2.f)
		, m_world(std::make_unique<GameLevel>(this))
	{}

	Application::~Application()
	{
		delete instance;
	}

	void Application::Run()
	{
		float accumulatedTime = 0.f;
		float cleanTimer = 0.f;

		m_world->BeginPlay();

		while (m_renderWindow.isOpen())
		{		
			sf::Event event;

			while (m_renderWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_renderWindow.close();
			}

			float targetDeltaTime = 1.f / m_targetFramerate;
			accumulatedTime += m_gameClock.restart().asSeconds();

			if (accumulatedTime >= targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;		
				PhysicsEngine::Instance().FixedUpdate(targetDeltaTime);
				Tick(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	void Application::Tick(float deltaTime)
	{
		if (m_world)
			m_world->TickInternal(deltaTime);		

		if (m_cleanClock.getElapsedTime().asSeconds() >= m_cleanInterval)
		{
			m_cleanClock.restart();
			m_world->Clean();
		}
	}

	void Application::Render()
	{
		if (!m_world)
			return;

		m_world->Render(m_renderWindow);
	}

	void Application::RenderInternal()
	{
		m_renderWindow.clear();
		Render();
		m_renderWindow.display();
	}

	Application* Application::instance = nullptr;

	Application& Application::Instance()
	{
		if (!instance)
			instance = new Application();

		return *instance;
	}
}