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

		Actor(const hop::Transform & transform) :
			m_transform{ transform }
		{}


		virtual void Update(float dt);
		virtual void Draw(hop::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		float GetRadius() { return 10.0f; };
		virtual void OnCollision(Actor* other) {};

		template<typename T>
		T* getComponent();

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		hop::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;
	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;

	};
	template<typename T>
	inline T* Actor::getComponent()
	{
		for (auto& component : m_components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}