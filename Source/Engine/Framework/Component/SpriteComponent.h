#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
namespace hop
{
	class SpriteComponent : public RenderComponent
	{
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		
		float GetRadius() override { return m_texture->GetSize().length() * 0.5f; }
	public:
		res_t<Texture> m_texture;
	};
}