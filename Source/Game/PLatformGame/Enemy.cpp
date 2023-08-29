#include "Enemy.h"
#include "Player.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "PlatformGame.h"
#include <cmath>

namespace hop {
	CLASS_DEFINITION(Enemy);


	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = getComponent<hop::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{

		Actor::Update(dt);

		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			hop::vec2 direction = player->transform.position - transform.position;
		}
		float dir = 0;

		//if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		//if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		hop::vec2 forward = hop::vec2{ 1, 0 };

		m_physicsComponent->ApplyForce(forward * m_speed * dir);



	}

	void Enemy::OnCollisionEnter(Actor* actor)
	{
		if (actor->tag == "Enemy") {
			destroyed = true;
		}

	}

	void Enemy::OnCollisionExit(Actor* actor)
	{

	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, m_speed);
	}

}

