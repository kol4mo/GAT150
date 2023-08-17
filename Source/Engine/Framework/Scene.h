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

		Actor* GetActor(std::string tag);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		bool load(const std::string& filename);

		void Read(const json_t& value);

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};


}