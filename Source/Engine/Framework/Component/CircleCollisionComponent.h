#pragma once
#include "CollisionComponent.h"

namespace hop {
	class CircleCollisionComponent : public CollisionComponent {
	public:
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}