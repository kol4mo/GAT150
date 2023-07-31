#include "Actor.h"

namespace hop
{
	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
				m_destroyed = (m_lifespan <= 0);
		}

		m_transform.position += m_velocity * dt;
	
		m_velocity.x = 0;
		m_velocity.y = 0;
		//m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void Actor::Draw(hop::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
