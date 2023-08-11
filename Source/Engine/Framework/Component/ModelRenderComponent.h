#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace hop
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
			void Update(float dt) override;
			void Draw(class Renderer& renderer) override;
			float GetRadius() override { return m_model->getRadius(); }
	public:
		res_t<Model> m_model;
	};
}