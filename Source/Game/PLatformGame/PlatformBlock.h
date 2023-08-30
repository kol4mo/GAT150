#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/PhysicsComponent.h"
#include "Framework/Component/Box2DCollisionComponent.h"
#include "Renderer/Model.h"

namespace hop {

	class PlatformBlock : public hop::Actor
	{
	public:

		ClASS_DECLERATION(PlatformBlock)


			bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;
		void OnCollisionExit(Actor* actor) override;

	private:
		float m_timerOne = -1;
		float m_timerTwo = -1;

		hop::PhysicsComponent* m_physicsComponent = nullptr;
		hop::Box2DCollisionComponent* m_collisionComponent = nullptr;
	};
}