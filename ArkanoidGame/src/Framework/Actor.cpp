#include "Framework/Actor.h"
#include "Framework/Core.h"

namespace Arkanoid
{
	Actor::Actor(World* owner, const sf::Vector2f& position, float rotation)
		: m_owner(owner)
		, m_isBeganPlay(false)
		, m_shape(nullptr)
	{
		//LOG("Actor spawned!");
	}

	void Actor::BeginPlayInternal()
	{
		if (m_isBeganPlay)
			return;
		
		BeginPlay();
		m_isBeganPlay = true;
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (IsPendingToDestroy())
			return;

		Tick(deltaTime);		
	}

	void Actor::AddPositionOffset(const sf::Vector2f& offset)
	{
		SetPosition(GetPosition() + offset);
	}

	void Actor::AddRotationOffset(float offset)
	{
		SetRotation(GetRotation() + offset);
	}

	void Actor::Render(sf::RenderWindow& window) const
	{
		if (IsPendingToDestroy())
			return;

		window.draw(*m_shape);
	}

	void Actor::BeginPlay()
	{
		//LOG("Actor begin play!");
	}

	void Actor::Tick(float deltaTime)
	{
		//LOG("Actor ticking!");
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bounds = m_shape->getGlobalBounds();
		m_shape->setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	}
}

