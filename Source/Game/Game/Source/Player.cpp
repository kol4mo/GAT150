#include "Player.h"
#include "Input/InputSystem.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "FunGame.h"
#include <cmath>

void Player::Update(float dt)
{

	Actor::Update(dt);
	hop::vec2 forward = hop::vec2{ 0,0 };
	if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) forward += {-1, 0};
	if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) forward += {1, 0};
	if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) forward += {0,-1};
	if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) forward += {0, 1};

	//if ((std::fabs(forward.x) + std::fabs(forward.y)) == 2) {
		//forward * 0.707;
	//}


	addForce(forward * m_speed);

	//m_transform.position += forward * m_speed * hop::g_time.GetDeltaTime();
	m_transform.position.x = hop::Wrap(m_transform.position.x, hop::g_renderer.GetWidth());
	m_transform.position.y = hop::Wrap(m_transform.position.y, hop::g_renderer.GetHeight());

	if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !hop::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

		hop::Transform transform{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400.0f, m_transform, m_model );
		m_scene->Add(std::move(weapon));

	}
	if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) hop::g_time.SetTimeScale(0.25f);
	else hop::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->m_tag == "Enemy" && dynamic_cast<FunGame*>(m_game)->getState() == FunGame::eState::Game) {
		dynamic_cast<FunGame*>(m_game)->SetState(FunGame::eState::PlayerDeadstart);
		hop::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = hop::PI;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = hop::Color{ 1, 0, 0, 1 };
		hop::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<hop::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	if (actor->m_tag == "PowerUp") {
		dynamic_cast<FunGame*>(m_game)->AddPoints(50);
	}
}


