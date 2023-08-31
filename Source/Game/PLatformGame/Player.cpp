#include "Player.h"
#include "Interactable.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "PlatformGame.h"
#include <cmath>

namespace hop {
	CLASS_DEFINITION(Player);


	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = getComponent<hop::PhysicsComponent>();
		m_SpriteComponent = getComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Player::Update(float dt)
	{

		Actor::Update(dt);
		
		vec2 velocity = m_physicsComponent->m_velocity;
		bool onGround = (groundCount > 0);
		//move
		float dir = 0;

		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_E)) {

			if (m_scene->GetActorByName("Rollback")) {
				m_scene->GetActorByName("Rollback")->destroyed = true;
			}

			SavedPosition = transform.position;
			auto rollback = INSTANTIATE(Actor, "Rollback");
			rollback->transform.position = SavedPosition;
			rollback->Initialize();
			m_scene->Add(std::move(rollback));
		}
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_F) && SavedPosition.x != -1 && SavedPosition.y != -1) {

			m_scene->GetActorByName("Rollback")->destroyed = true;
			m_physicsComponent->setPosition(SavedPosition);
			transform.position = SavedPosition;
			SavedPosition = { -1, -1 };

		}
		
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		if (dir) {
			hop::vec2 forward = hop::vec2{ 1, 0 };
			velocity.x += m_speed * dir * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
		}
		//m_physicsComponent->SetVelocity(forward * m_speed * dir );
		 

		//jump
		if ( onGround && hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !hop::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			hop::vec2 up = hop::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * m_jump);
		}

		//animation
		if (std::fabs(velocity.x) > 0.2f) {
			if (dir!= 0) m_SpriteComponent->flipH = (velocity.x < 0);
			m_SpriteComponent->SetSequence("run");
		}
		else {
			m_SpriteComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* actor)
	{
		if (actor->tag == "Enemy") {
			destroyed = true;
		}		
		if (actor->tag == "Coin") {
			coins++;
		}
		if (actor->tag == "Key") {
			hasKey = true;
		}
		if (actor->tag == "Ground") groundCount++;
		if (actor->tag == "Win" && hasKey) {
			win = true;
		}
	}

	void Player::OnCollisionExit(Actor* actor)
	{
		if (actor->tag == "Ground") groundCount--;
	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, m_jump);
		READ_DATA(value, maxSpeed);
	}

}

