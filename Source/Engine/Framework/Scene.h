#pragma once
#include <list>
#include <string>
#include "Actor.h"

namespace hop
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		int getLength() { return (int)m_actors.size(); }

		template<typename T = Actor>
		T* GetActor();
		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		bool load(const std::string& filename);

		void Read(const json_t& value);

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};
	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors) {
			T* result = dynamic_cast<T*> (actor.get());
			if (result) return result;
		}
		return nullptr;
	}
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			T* result = dynamic_cast<T*> (actor.get());
			if (result && actor->name == name) return result;
		}
		return nullptr;
	}


}