#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/PhysicsComponent.h"
#include "Renderer/Model.h"

namespace hop {

	class Enemy : public hop::Actor
	{
	public:

		ClASS_DECLERATION(Enemy)


			bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;
		void OnCollisionExit(Actor* actor) override;

	private:
		float m_speed = 0;

		hop::PhysicsComponent* m_physicsComponent = nullptr;
	};
}