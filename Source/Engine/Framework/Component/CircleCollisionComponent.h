#pragma once
#include "CollisionComponent.h"

namespace hop {
	class CircleCollisionComponent : public CollisionComponent {
	public:
		ClASS_DECLERATION(CircleCollisionComponent)
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}