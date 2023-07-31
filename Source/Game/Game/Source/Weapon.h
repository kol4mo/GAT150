#pragma once
#include "Framework/Actor.h"

class Weapon : public hop::Actor
{
public:
	Weapon(float speed, const hop::Transform& transform, std::shared_ptr<hop::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;
};