#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/PhysicsComponent.h"
#include "Renderer/Model.h"

namespace hop {

	class Player : public hop::Actor
	{
	public:

		ClASS_DECLERATION(Player)

		Player(float speed, float turnRate, const hop::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{}

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollision(Actor* actor) override;
		Player() = default;
	private:
		float m_speed = 0;
		float m_turnRate = 0;

		hop::PhysicsComponent* m_physicsComponent = nullptr;
	};
}