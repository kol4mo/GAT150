#include "Scene.h"
#include "Framework/Component/CollisionComponent.h"

namespace hop
{
	bool Scene::Initialize()
	{
		for (auto& actor : m_actors) actor->Initialize();

		return true;
	}
	void Scene::Update(float dt)
	{
		for (auto& actor : m_actors) { 
			actor->Update(dt); 
		}

		auto iter = m_actors.begin();
		while (iter != m_actors.end())
			iter = ((*iter)->destroyed) ? m_actors.erase(iter) : ++iter;


		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {
				CollisionComponent* collision1 = (*iter1)->getComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->getComponent<CollisionComponent>();

				if (collision1 == nullptr || collision2 == nullptr) continue;

				if (collision1->CheckCollision(collision2)) {

					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
		}

	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors) actor->Draw(renderer);
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		m_actors.clear();
	}

	bool Scene::load(const std::string& filename)
	{
		rapidjson::Document document;
		if (Json::Load(filename, document)) {
			ERROR_LOG("Could not load scene file: " << filename);
			return false;
		}
		Read(document);

		return true;
	}

	void Scene::Read(const json_t& value)
	{
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
		{
			for (auto& actorValue : GET_DATA(value, actors).GetArray()) {
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);
				actor->Read(actorValue);
				Add(std::move(actor));
			}
		}
	}

	Actor* Scene::GetActor(std::string tag)
	{
		for (auto& actor : m_actors) {
			Actor* result = dynamic_cast<Actor*> (actor.get());
			if (result && actor->tag == tag) return result;
		}
		return nullptr;
	}
}