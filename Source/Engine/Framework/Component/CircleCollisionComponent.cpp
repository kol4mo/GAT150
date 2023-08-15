#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace hop {

    CLASS_DEFINITION(CircleCollisionComponent)
    void hop::CircleCollisionComponent::Update(float dt)
    {
    }

    bool hop::CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->m_transform.position.Distance(collision->GetOwner()->m_transform.position);
        float radius = m_radius + collision->m_radius;

        if (distance <= radius) return true;

        return false;
    }
}
