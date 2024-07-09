#include "Framework/Entity.h"

namespace Arkanoid
{
	Entity::Entity()
		: m_bIsPendingToDestroy(false)
	{}

	Entity::~Entity()
	{
		LOG("Actor destroyed!");
	}

	void Entity::Destroy()
	{
		m_bIsPendingToDestroy = true;
	}

	bool Entity::IsPendingToDestroy() const
	{
		return m_bIsPendingToDestroy;
	}
}