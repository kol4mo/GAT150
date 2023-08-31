#include "PlatformGame.h"
#include "Framework/Framework.h"
#include "PLayer.h"
#include "Core/core.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool PlatformGame::Initialize()
{

	hop::g_audioSystem.AddAudio("explode", "explode.wav");
	hop::g_audioSystem.AddAudio("song", "song.wav");

	hop::g_audioSystem.PlayOneShot("song", true);

	m_scene = std::make_unique<hop::Scene>();
	m_scene->load("Scenes/Scene.json");
	m_scene->load("Scenes/tilemap.json");
	m_scene->Initialize();
	EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
	hop::EventManager::instance().subscribe("OnPlayerDead", this, std::bind(&PlatformGame::OnPlayerDead, this, std::placeholders::_1));


	return true;
}

void PlatformGame::shutdown()
{
}

void PlatformGame::update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
	{
		m_state = PlatformGame::eState::StartGame;
	}
		break;
	case PlatformGame::eState::StartGame:
	{

		m_scene->GetActorByName("Title")->active = false;
		m_state = PlatformGame::eState::StartLevel;
	}
		
		break;
	case PlatformGame::eState::StartLevel:
	{
		auto actor = INSTANTIATE(Actor, "Crate");
		actor->transform.position = { 134, 563 };
		actor->Initialize();
		m_scene->Add(std::move(actor));
		auto b1 = INSTANTIATE(Actor, "DissapearingBlock");
		b1->Initialize();
		m_scene->Add(std::move(b1));
		auto b2 = INSTANTIATE(Actor, "DissapearingBlock");
		b2->transform.position = { 304, 112 };
		b2->Initialize();
		m_scene->Add(std::move(b2));
		auto b3 = INSTANTIATE(Actor, "DissapearingBlock");
		b3->transform.position = { 400, 112 };
		b3->Initialize();
		m_scene->Add(std::move(b3));
		auto coin1 = INSTANTIATE(Actor, "Coin");
		coin1->transform.position = { 304, 80 };
		coin1->Initialize();
		m_scene->Add(std::move(coin1));
		auto coin2 = INSTANTIATE(Actor, "Coin");
		coin2->transform.position = { 752, 80 };
		coin2->Initialize();
		m_scene->Add(std::move(coin2));
		auto d1 = INSTANTIATE(Actor, "Danger");
		d1->transform.position = { 476, 128 };
		d1->Initialize();
		m_scene->Add(std::move(d1));
		auto d2 = INSTANTIATE(Actor, "Danger");
		d2->transform.position = { 476 + 64, 480 - 32 };
		d2->Initialize();
		m_scene->Add(std::move(d2));
		auto player = INSTANTIATE(Actor, "Player");
		player->Initialize();
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
	break;
	case PlatformGame::eState::Game: 
		if (m_scene->GetActorByName("Player") == nullptr) {
			auto player = INSTANTIATE(Actor, "Player");
			player->Initialize();
			m_scene->Add(std::move(player));
		}
		if (m_scene->GetActorByName("Player") != nullptr && dynamic_cast<hop::Player*>(m_scene->GetActorByName("Player"))->win) {
			m_scene->GetActorByName("Title")->active = true;
		}
		break;
	case eState::PlayerDeadstart:
		break;
	case PlatformGame::eState::PlayerDead:

		break;
	case PlatformGame::eState::GameOver:
		break;
	default:
		break;
	}



	m_scene->Update(dt);
}

void PlatformGame::draw(hop::Renderer& renderer)
{

	m_scene->Draw(renderer);
	hop::g_particleSystem.Draw(renderer);
}

void PlatformGame::OnAddPoints(const hop::Event& event)
{
	m_score += std::get<int>(event.data);

}

void PlatformGame::OnPlayerDead(const hop::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadstart;
}
