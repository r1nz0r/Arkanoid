#include "Game/Block.h"
#include "Game/GameSettings.h"

namespace Arkanoid
{
	Block::Block(World* owner)
		: PhysicsActor(owner, std::unique_ptr<Rectangle>(new Rectangle({ 0.f, 0.f }, { BLOCK_WIDTH, BLOCK_HEIGHT })))
	{
		m_shape.reset(new sf::RectangleShape({ BLOCK_WIDTH, BLOCK_HEIGHT }));
		CenterPivot();
	}

	void Block::Tick(float deltaTime)
	{}

	void Block::BeginPlay()
	{
		PhysicsActor::BeginPlay();
		m_shape->setFillColor(sf::Color::Magenta);
	}

	void Block::OnCollisionEnter(const ICollidable & other)
	{
		Destroy();
	}

	void Block::SetPosition(const sf::Vector2f & newPosition)
	{
		PhysicsActor::SetPosition(newPosition);

		if (m_collider)
			m_collider->SetPosition({ GetPosition().x - BLOCK_WIDTH / 2.f, GetPosition().y - BLOCK_HEIGHT / 2.f });
	}
}