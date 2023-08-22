#include "Player.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "FunGame.h"
#include <cmath>

namespace hop {
	CLASS_DEFINITION(Player)


		bool Player::Initialize()
	{
		Actor::Initialize();

		//cache off
		m_physicsComponent = getComponent<hop::PhysicsComponent>();
		auto collisionComponent = getComponent<hop::CollisionComponent>();
		if (collisionComponent) {
			auto renderComponent = getComponent<hop::RenderComponent>();

			if (renderComponent) {

				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}


		return true;
	}

	void Player::Update(float dt)
	{

		Actor::Update(dt);
		hop::vec2 forward = hop::vec2{ 0,0 };
		float thrust = 0;
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) forward += {-1, 0}; thrust = 1;
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) forward += {1, 0}; thrust = 1;
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) forward += {0, -1}; thrust = 1;
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) forward += {0, 1}; thrust = 1;

		//if ((std::fabs(forward.x) + std::fabs(forward.y)) == 2) {
			//forward * 0.707;
		//}

		auto physicsComponent = m_physicsComponent;
		physicsComponent->ApplyForce(forward * m_speed * thrust);

		//m_transform.position += forward * m_speed * hop::g_time.GetDeltaTime();
		transform.position.x = (float)hop::Wrap((int)transform.position.x, (int)hop::g_renderer.GetWidth());
		transform.position.y = (float)hop::Wrap((int)transform.position.y, (int)hop::g_renderer.GetHeight());


		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) hop::g_time.SetTimeScale(0.25f);
		else hop::g_time.SetTimeScale(1.0f);
	}

	void Player::OnCollision(Actor* actor)
	{
		if (actor->tag == "Enemy" && dynamic_cast<FunGame*>(m_game)->getState() == FunGame::eState::Game) {
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
			hop::Transform transform{ { this->transform.position }, 0, 1 };
			auto emitter = std::make_unique<hop::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
		if (actor->tag == "PowerUp") {
			dynamic_cast<FunGame*>(m_game)->AddPoints(50);
		}
	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, m_speed);
	}

}

