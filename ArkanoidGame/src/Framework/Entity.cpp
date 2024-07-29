#include "Framework/Entity.h"

namespace Arkanoid
{
	uint64_t Entity::s_UniqueId = 0;

	Entity::Entity()
		: m_bIsPendingToDestroy(false)
		, m_Id(GetNextUniqueId())
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