#pragma once
#include "Core/core.h"
#include "Renderer/Model.h"
#include "Framework/Component/Component.h"
#include <memory>
#include "Object.h"

namespace hop
{
	class Actor : public Object
	{
	public:
		ClASS_DECLERATION(Actor)

		Actor() = default;

		Actor(const hop::Transform & transform) :
			transform{ transform }
		{}
		virtual ~Actor() {
			OnDestroy();
		}
		Actor(const Actor& other);	

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(hop::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		virtual void OnCollisionEnter(Actor* other) {};
		virtual void OnCollisionExit(Actor* other) {};

		template<typename T>
		T* getComponent();

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		hop::Transform transform;
		std::string tag;

		float lifespan = -1.0f;

		bool destroyed = false;
	protected:
		std::vector<std::unique_ptr<Component>> components;

		bool persistent = false;
		bool prototype = false;

	};
	template<typename T>
	inline T* Actor::getComponent()
	{
		for (auto& component : components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}