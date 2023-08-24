#include "FunGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Framework.h"
#include "Core/core.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool FunGame::Initialize()
{

	m_scoreText = std::make_unique<hop::Text>(GET_RESOURCE(hop::Font, "Arcade.ttf", 58));
	m_scoreText->Create(hop::g_renderer, "SCORE 0000", hop::Color(1, 1, 1, 1));
	m_lifeText = std::make_unique<hop::Text>(GET_RESOURCE(hop::Font, "Arcade.ttf", 58));
	m_lifeText->Create(hop::g_renderer, "Lives: 0", hop::Color(1, 1, 1, 1));
	hop::g_audioSystem.AddAudio("explode", "explode.wav");
	hop::g_audioSystem.AddAudio("song", "song.wav");
	
	hop::g_audioSystem.PlayOneShot("song", true);

	m_scene = std::make_unique<hop::Scene>();
	m_scene->load("Scenes/SpaceScene.json");
	m_scene->Initialize();
	
	EVENT_SUBSCRIBE("OnAddPoints", FunGame::OnAddPoints);
	hop::EventManager::instance().subscribe("OnPlayerDead", this, std::bind(&FunGame::OnPlayerDead, this, std::placeholders::_1));


	return true;
}

void FunGame::shutdown()
{
}

void FunGame::update(float dt)
{
	switch (m_state)
	{
	case FunGame::eState::Title:
		m_scene->GetActorByName("Title")->active = true;
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			auto actor = m_scene->GetActorByName<hop::Actor>("Background");
			if (actor) actor->active = false;
		}
		break;
	case FunGame::eState::StartGame:

		m_scene->GetActorByName("Title")->active = false;
		m_score = 0;
		m_lives = 3;
		m_level = 0;
		m_state = eState::StartLevel;
		break;
	case FunGame::eState::StartLevel:
	{	
		m_scene->RemoveAll();

		if (hop::random(2) == 0) {
			auto powerup = INSTANTIATE(Enemy, "enemy1");
			powerup->m_game = this;
			powerup->Initialize();
			powerup->m_speed = 0;
			powerup->tag = "PowerUp";
			powerup->transform = hop::Transform{ {hop::random(hop::g_renderer.GetWidth()), hop::random(hop::g_renderer.GetHeight())}, 0, 1 };
			powerup->getComponent<hop::SpriteComponent>()->m_texture = GET_RESOURCE(hop::Texture, "power-UP.png", hop::g_renderer);
			m_scene->Add(std::move(powerup));

		}

		difcur = (int)std::fabs((30* std::sin(10*(m_level-1))));
		for (int i = 0; i < difcur; i++) {
			auto enemy = INSTANTIATE(Enemy, "enemy1");
			enemy->m_game = this;
			enemy->Initialize();
			enemy->transform = enemy->randomWallPos(1.5f);
			m_scene->Add(std::move(enemy));
		}		
		difcur = (int)std::fabs(30* (1- fabs(std::sin(5*(m_level-1)))));
		for (int i = 0; i < difcur; i++) {
			auto enemy = INSTANTIATE(Enemy, "enemy1");
			enemy->m_game = this;
			enemy->Initialize();
			enemy->transform = enemy->randomWallPos(1.0f);
			enemy->m_speed = 12;
			m_scene->Add(std::move(enemy));
		}

		auto player = INSTANTIATE(Player, "player");
		player->m_game = this;
		player->Initialize();
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case FunGame::eState::Game: {

		if (m_scene->GetActor<hop::Actor>("Enemy") == nullptr) {
			m_state = eState::StartLevel;
			m_level++;
			hop::EventManager::instance().DispatchEvent("OnAddPoints", 14);
			//AddPoints(14);
		}
	}
		break;
	case eState::PlayerDeadstart:
		m_stateTimer = 3;
		m_state = eState::PlayerDead;
		break;
	case FunGame::eState::PlayerDead:

		m_scene->RemoveAll();
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			if (m_lives <= 0) {m_state = eState::GameOver;
			}
			else {
				m_state = eState::StartLevel;
			}
		}

		break;
	case FunGame::eState::GameOver:
		break;
	default:
		break;
	}

	m_scoreText->Create(hop::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_lifeText->Create(hop::g_renderer, "lives: " + std::to_string(m_lives), {1, 1, 1, 1});

	m_scene->Update(dt);
}

void FunGame::draw(hop::Renderer& renderer)
{

	m_scene->Draw(renderer);
	hop::g_particleSystem.Draw(renderer);

	m_scoreText->Draw(renderer, 40, 40);
	m_lifeText->Draw(renderer, 800, 40);
}

void FunGame::OnAddPoints(const hop::Event& event)
{
	m_score += std::get<int>(event.data);

}

void FunGame::OnPlayerDead(const hop::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadstart;
}
