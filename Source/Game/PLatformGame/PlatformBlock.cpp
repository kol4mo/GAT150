#include "PlatformBlock.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "PlatformGame.h"
#include <cmath>

namespace hop {
	CLASS_DEFINITION(PlatformBlock);


	bool PlatformBlock::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = getComponent<hop::PhysicsComponent>();
		m_collisionComponent = getComponent<hop::Box2DCollisionComponent>();

		return true;
	}

	void PlatformBlock::Update(float dt)
	{
		if (m_timerOne != -1) {
			m_timerOne -= dt;
		}
		if (m_timerTwo != -1) {
			m_timerTwo -= dt;
		}


		Actor::Update(dt);

		if (m_timerOne < 0 && m_timerOne != -1) {
			m_timerTwo = 2;
			m_timerOne = -1;
			m_collisionComponent->setTrigger(true);
			active = false;
		}

		if (m_timerTwo < 0 && m_timerTwo != -1) {
			m_timerTwo = -1;
			m_collisionComponent->setTrigger(false);
			active = true;
		}




	}

	void PlatformBlock::OnCollisionEnter(Actor* actor)
	{
		if (actor->tag == "player") {
			m_timerOne = 3;
		}

	}

	void PlatformBlock::OnCollisionExit(Actor* actor)
	{

	}

	void PlatformBlock::Read(const json_t& value) {
		Actor::Read(value);

	}

}

