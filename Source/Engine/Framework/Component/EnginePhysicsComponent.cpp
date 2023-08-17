#include "EnginePhysicsComponent.h"

#include "Framework/Actor.h"

namespace hop {

	EnginePhysicsComponent::Register register_class;
	void hop::EnginePhysicsComponent::Update(float dt)
	{
		m_owner->transform.position += m_velocity * dt;
		m_velocity = std::pow(1 - m_damping, dt);
	}

	void hop::EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}
}
