#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/SpriteAnimRenderComponent.h"
#include "Renderer/Model.h"

namespace hop {

	class Collectable : public hop::Actor
	{
	public:

		ClASS_DECLERATION(Collectable)


			bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;
		void OnCollisionExit(Actor* actor) override;

	private:

	};
}