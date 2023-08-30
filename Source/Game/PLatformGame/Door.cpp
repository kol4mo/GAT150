
#include "Door.h"
#include "Interactable.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "PlatformGame.h"
#include <cmath>

namespace hop {
	CLASS_DEFINITION(Door);


	bool Door::Initialize()
	{
		Actor::Initialize();


		return true;
	}

	void Door::Update(float dt)
	{

		Actor::Update(dt);

		if (dynamic_cast<Interactable*>(m_scene->GetActorByName("Lever"))->activeLever) {
			destroyed = true;
		}



	}

	void Door::OnCollisionEnter(Actor* actor)
	{


	}

	void Door::OnCollisionExit(Actor* actor)
	{

	}

	void Door::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, active);
	}

}

