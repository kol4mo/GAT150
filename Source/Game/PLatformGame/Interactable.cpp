
#include "Interactable.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "PlatformGame.h"
#include <cmath>

namespace hop {
	CLASS_DEFINITION(Interactable);


	bool Interactable::Initialize()
	{
		Actor::Initialize();

		m_spriteRender = getComponent<hop::SpriteAnimRenderComponent>();

		return true;
	}

	void Interactable::Update(float dt)
	{

		Actor::Update(dt);


			if (hop::g_inputSystem.GetMouseButtonDown(0) && playerC) {
				activeLever = true;
				m_spriteRender->SetSequence("Active");
			}



	}

	void Interactable::OnCollisionEnter(Actor* actor)
	{
		if (actor->tag == "Player") {
			playerC = true;
		}

	}

	void Interactable ::OnCollisionExit(Actor* actor)
	{
		if (actor->tag == "Player") {
			playerC = false;
		}
	}

	void Interactable::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, active);
	}

}

