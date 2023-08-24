#pragma once
#include "Framework/Actor.h"
#include "Core/math/Vexctor2.h"
#include "Framework/Component/Box2DPhysicsComponent.h"

namespace hop {
	class Enemy : public hop::Actor
	{
	public:

		ClASS_DECLERATION(Enemy)

		Enemy(float speed, float turnRate, const hop::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{
			m_fireTime = 2.0f;
			m_fireTimer = m_fireTime;
		}

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;

		Enemy() = default;
		hop::Transform randomWallPos(float scale);
		float m_speed = 0;
	private:
		float m_turnRate = 0;

		float m_fireTime = 0;
		float m_fireTimer = 0;

		hop::PhysicsComponent* m_physicsComponent;
	};
}
