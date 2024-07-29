#pragma once
#include "Framework/Core.h"
#include <cstdint>

namespace Arkanoid
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void Destroy();
		bool IsPendingToDestroy() const;
		uint64_t GetId() const { return m_Id; }

	private:
		uint64_t GetNextUniqueId() const { return s_UniqueId++; }
		bool m_bIsPendingToDestroy;
		static uint64_t s_UniqueId;
		uint64_t m_Id;
	};
}