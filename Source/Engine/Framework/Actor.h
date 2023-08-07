#pragma once
#include "Core/core.h"
#include "Renderer/Model.h"
#include "Framework/Component/Component.h"
#include <memory>

namespace hop
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const hop::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}
		Actor(const hop::Transform & transform) :
			m_transform{ transform }
		{}


		virtual void Update(float dt);
		virtual void Draw(hop::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		float GetRadius() { return (m_model) ? m_model->getRadius() * m_transform.scale : 0; }
		virtual void OnCollision(Actor* other) {};

		void addForce(const vec2& force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		hop::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;
	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;

		std::shared_ptr<hop::Model> m_model;

		vec2 m_velocity;
		float m_damping = 0;
	};
}