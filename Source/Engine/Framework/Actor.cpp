#include "Actor.h"
#include "Component/RenderComponent.h"

namespace hop
{
	CLASS_DEFINITION(Actor)

	bool Actor::Initialize()
	{
		for (auto& component : components) {
			component->Initialize();
		}

		return true;
	}
	void Actor::OnDestroy()
	{
		for (auto& component : components) {
			component->OnDestroy();
		}
	}
	void Actor::Update(float dt) {
		if (lifespan != -1.0f) {
			lifespan -= dt;
				destroyed = (lifespan <= 0);
		}
		for (auto& component : components) {
			component->Update(dt);
		}

		//m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void Actor::Draw(hop::Renderer& renderer)
	{
		for (auto& component : components) {
			if (dynamic_cast<RenderComponent*>(component.get())) {
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}

		//m_model->Draw(renderer, m_transform);
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		components.push_back(std::move(component));
	}

	void Actor::Read(const rapidjson::Value& value)
	{
		Object::Read(value);
		READ_DATA(value, tag);
		READ_DATA(value, lifespan);

		if (HAS_DATA(value, transform)) transform.Read(value);

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray()) {
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}
	}
}
