#pragma once
#include "PhysicsComponent.h"

namespace hop
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		ClASS_DECLERATION(EnginePhysicsComponent)
		// Inherited via PhysicsComponent
		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;

		// Inherited via PhysicsComponent
		virtual void ApplyTorque(const float torque) override;
	};

}