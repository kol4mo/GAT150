#pragma once
#include "Framework/Actor.h"
#include "Framework/Component/SpriteAnimRenderComponent.h"
#include "Renderer/Model.h"

namespace hop {

	class Interactable : public hop::Actor
	{
	public:

		ClASS_DECLERATION(Interactable)


			bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor) override;
		void OnCollisionExit(Actor* actor) override;
		bool activeLever = false;
		bool playerC = false;

	private:

		SpriteAnimRenderComponent* m_spriteRender = nullptr;
	};
}