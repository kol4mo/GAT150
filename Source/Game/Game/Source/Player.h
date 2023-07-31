#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"


class Player : public hop::Actor
{
public:
	Player(float speed, float turnRate, const hop::Transform& transform, std::shared_ptr<hop::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{turnRate}
	{}
	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};