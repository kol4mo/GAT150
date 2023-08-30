
#include "Collectable.h"
#include "Interactable.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "PlatformGame.h"
#include <cmath>

namespace hop {
	CLASS_DEFINITION(Collectable);


	bool Collectable::Initialize()
	{
		Actor::Initialize();


		return true;
	}

	void Collectable::Update(float dt)
	{

		Actor::Update(dt);




	}

	void Collectable::OnCollisionEnter(Actor* actor)
	{
		if (actor->tag == "Player") destroyed = true;

	}

	void Collectable::OnCollisionExit(Actor* actor)
	{

	}

	void Collectable::Read(const json_t& value) {
		Actor::Read(value);

	}

}

