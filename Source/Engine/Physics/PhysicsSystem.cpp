#include "PhysicsSystem.h"
namespace hop
{
	bool PhysicsSystem::Initialize()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = std::make_unique<b2World>(gravity);
		return true;
	}
	void PhysicsSystem::Update(float dt)
	{
		//
	}
}

