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

		hop::vec2 forward = hop::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			hop::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * m_speed);
		}



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

