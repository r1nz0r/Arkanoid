#include "SFML/Graphics.hpp"
#include "Framework/Application.h"
#include "Framework/Entity.h"

namespace Arkanoid
{
	class Actor;
	class Ball;
	class Paddle;
	class World : public Entity
	{
	public:
		World(Application* owner);
		~World() = default;

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Render(sf::RenderWindow& window) const;
		// We need to remove all actors marked for deletion in previous frame.
		void Clean();
		void HandleInput();
		std::weak_ptr<Paddle> GetPaddle() const { return m_paddle; }
		inline sf::Vector2u GetWindowSize() const { return m_owner->GetWindowSize(); };

		template<class ActorType, typename... Args>
		std::weak_ptr<ActorType> SpawnActor(Args... args);

	private:
		std::vector<std::shared_ptr<Actor>> m_actors; // All alive actors in world
		std::vector<std::shared_ptr<Actor>> m_pendingActors; // Actors to be spawned in next tick
		std::weak_ptr<Ball> m_ball;
		std::weak_ptr<Paddle> m_paddle;
		Application* m_owner;

	};

	template<class ActorType, typename ...Args>
	inline std::weak_ptr<ActorType> World::SpawnActor(Args ...args)
	{
		static_assert(std::is_base_of<Actor, ActorType>::value, "ActorType must be derrived from Actor class");
		auto newActor = std::make_shared<ActorType>(this, args...);
		m_pendingActors.push_back(newActor);
		return newActor;
	}
}