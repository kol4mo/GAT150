#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"


class Player : public hop::Actor
{
public:
	Player(float speed, float turnRate, const hop::Transform& transform) :
		Actor{ transform},
		m_speed{ speed },
		m_turnRate{turnRate}
	{}
	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};