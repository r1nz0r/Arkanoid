#pragma once
#include "Framework/Core.h"

namespace Arkanoid
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void Destroy();
		bool IsPendingToDestroy() const;
	private:
		bool m_bIsPendingToDestroy;
	};
}