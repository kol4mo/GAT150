#pragma once
#include "Framework/Object.h"

namespace hop
{
	class Component : public Object
	{
	public:
		virtual void Update(float dt) = 0;

		friend class Actor;



		 class Actor* m_owner = nullptr;
	protected:
	};
}