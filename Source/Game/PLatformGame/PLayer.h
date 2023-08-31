#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/PhysicsComponent.h"
#include "Renderer/Model.h"

namespace hop {

	class Player : public hop::Actor
	{
	public:

		ClASS_DECLERATION(Player)


		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;
		void OnCollisionExit(Actor* actor) override;

		bool win = false;

	private:
		float m_speed = 0;
		float maxSpeed = 0;
		float m_jump = 0;

		int groundCount = 0;

		int coins = 0;
		bool hasKey = false;

		vec2 SavedPosition = {-1, -1};

		hop::PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_SpriteComponent = nullptr;
	};
}