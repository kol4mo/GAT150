#include "Actor.h"
#include "Component/RenderComponent.h"

namespace hop
{
	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
				m_destroyed = (m_lifespan <= 0);
		}
		for (auto& component : m_components) {
			component->Update(dt);
		}

		//m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void Actor::Draw(hop::Renderer& renderer)
	{
		for (auto& component : m_components) {
			if (dynamic_cast<RenderComponent*>(component.get())) {
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}

		//m_model->Draw(renderer, m_transform);
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}
}
