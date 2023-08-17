#include "ModelRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace hop {
	CLASS_DEFINITION(ModelRenderComponent)

		bool ModelRenderComponent::Initialize()
	{
		m_model = GET_RESOURCE(Model, modelName);

		return true;
	}

	void hop::ModelRenderComponent::Update(float dt)
	{

	}

	void hop::ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
	}

	void ModelRenderComponent::Read(const json_t& value) {
		READ_DATA(value, modelName);
	}
}
