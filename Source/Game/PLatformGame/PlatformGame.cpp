#include "PlatformGame.h"
#include "Framework/Framework.h"
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

		m_state = PlatformGame::eState::StartLevel;
	}
		
		break;
	case PlatformGame::eState::StartLevel:
	{
		auto actor = INSTANTIATE(Actor, "Crate");
		actor->transform.position = { 128, 500 };
		actor->Initialize();
		m_scene->Add(std::move(actor));

	}
	m_state = eState::Game;
	break;
	case PlatformGame::eState::Game: 
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
