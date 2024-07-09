#include "SFML/Graphics.hpp"
#include "Framework/Application.h"
#include "Framework/Entity.h"

namespace Arkanoid
{
	class Actor;
	class World : public Entity
	{
	public:
		World(Application* owner);
		~World() = default;

		virtual void BeginPlay();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window) const;
		// We need to remove all actors marked for deletion in previous frame.
		void Clean();

		template<class ActorType, typename... Args>
		std::weak_ptr<ActorType> SpawnActor(Args... args);

	protected:
		virtual void Tick(float deltaTime);
		Application* m_owner;

	private:
		std::vector<std::shared_ptr<Actor>> m_actors; // All alive actors in world
		std::vector<std::shared_ptr<Actor>> m_pendingActors; // Actors to be spawned in next tick
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