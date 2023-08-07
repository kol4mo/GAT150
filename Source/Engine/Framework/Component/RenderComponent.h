#pragma once
#include "Component.h"
namespace hop
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}