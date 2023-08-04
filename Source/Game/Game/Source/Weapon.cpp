#include "Weapon.h"

void Weapon::Update(float dt)
{
	Actor::Update(dt);
	hop::vec2 forward = hop::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * hop::g_time.GetDeltaTime();
	m_transform.position.x = (float)hop::Wrap((int)m_transform.position.x, (int)hop::g_renderer.GetWidth());
	m_transform.position.y = (float)hop::Wrap((int)m_transform.position.y, (int)hop::g_renderer.GetHeight());
}

void Weapon::OnCollision(Actor* actor)
{
	m_destroyed = true;
}
