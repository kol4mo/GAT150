#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace hop {
	CLASS_DEFINITION(ModelRenderComponent)

	void hop::ModelRenderComponent::Update(float dt)
	{

	}

	void hop::ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_transform);
	}
}
