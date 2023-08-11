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

	m_scoreText = std::make_unique<hop::Text>(hop::g_resources.Get<hop::Font>("Arcade.ttf", 58));
	m_scoreText->Create(hop::g_renderer, "SCORE 0000", hop::Color(1, 1, 1, 1));
	m_lifeText = std::make_unique<hop::Text>(hop::g_resources.Get<hop::Font>("Arcade.ttf", 58));
	m_lifeText->Create(hop::g_renderer, "Lives: 0", hop::Color(1, 1, 1, 1));
	m_startText = std::make_unique<hop::Text>(hop::g_resources.Get<hop::Font>("Arcade.ttf", 58));
	m_startText->Create(hop::g_renderer, "Press Space to Start", hop::Color(1, 1, 1, 1));
	hop::g_audioSystem.AddAudio("explode", "explode.wav");
	hop::g_audioSystem.AddAudio("song", "song.wav");
	
	hop::g_audioSystem.PlayOneShot("song", true);

	m_scene = std::make_unique<hop::Scene>();

	//for (int i = 0; i < (x * x); i++) {
	//	unique_ptr<Enemy> enemy = make_unique<Enemy>(200, 0, hop::Transform{{hop::random(hop::g_renderer.GetWidth()), hop::random(hop::g_renderer.GetHeight())}, hop::randomDir(), 3}, hop::g_modelManager.Get("S.txt"));
	//	enemy->m_tag = "Enemy";
	//	enemy->m_game = this;
	//	scene->Add(std::move(enemy));
	//}
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
		if (hop::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	case FunGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_level = 0;
		m_state = eState::StartLevel;
		break;
	case FunGame::eState::StartLevel:
	{	
		m_scene->RemoveAll();

		if (hop::random(2) == 0) {
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(0, 0, hop::Transform{ {hop::random(hop::g_renderer.GetWidth()), hop::random(hop::g_renderer.GetHeight())}, 0, 1});
			enemy->m_tag = "PowerUp";
			enemy->m_game = this;
			std::unique_ptr<hop::SpriteComponent> component = std::make_unique<hop::SpriteComponent>();
			component->m_texture = hop::g_resources.Get<hop::Texture>("power-UP.png", hop::g_renderer);
			enemy->AddComponent(std::move(component));
			auto CollisionComponent = std::make_unique<hop::CircleCollisionComponent>();
			CollisionComponent->m_radius = 10.0f;
			enemy->AddComponent(std::move(CollisionComponent));
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}

		difcur = (int)std::fabs((30* std::sin(10*(m_level-1))));
		for (int i = 0; i < difcur; i++) {
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(200, 0, enemy->randomWallPos(1.5f));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			std::unique_ptr<hop::SpriteComponent> component = std::make_unique<hop::SpriteComponent>();
			component->m_texture = hop::g_resources.Get<hop::Texture>("enemy.png", hop::g_renderer);
			enemy->AddComponent(std::move(component));
			auto CollisionComponent = std::make_unique<hop::CircleCollisionComponent>();
			CollisionComponent->m_radius = 10.0f;
			enemy->AddComponent(std::move(CollisionComponent));
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}		
		difcur = (int)std::fabs(30* (1- fabs(std::sin(5*(m_level-1)))));
		for (int i = 0; i < difcur; i++) {
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(300, 0, enemy->randomWallPos(1));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			std::unique_ptr<hop::SpriteComponent> component = std::make_unique<hop::SpriteComponent>();
			component->m_texture = hop::g_resources.Get<hop::Texture>("enemy.png", hop::g_renderer);
			enemy->AddComponent(std::move(component));
			auto CollisionComponent = std::make_unique<hop::CircleCollisionComponent>();
			CollisionComponent->m_radius = 10.0f;
			enemy->AddComponent(std::move(CollisionComponent));
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		//create player
		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, 0, hop::Transform{ {540, 270}, 0, 1 });
		player->m_tag = "player";
		player->m_game = this;
		//create components
		auto component = std::make_unique<hop::SpriteComponent>();
		component->m_texture = hop::g_resources.Get<hop::Texture>("player.png", hop::g_renderer);
		player->AddComponent(std::move(component));
		auto physicsComponent = std::make_unique<hop::EnginePhysicsComponent>();
		player->AddComponent(std::move(physicsComponent));

		auto CollisionComponent = std::make_unique<hop::CircleCollisionComponent>();
		CollisionComponent->m_radius = 10.0f;
		player->AddComponent(std::move(CollisionComponent));

		player->Initialize();
		m_scene->Add(std::move(player));
		//expand and aadd player->m_game = this;
	}
	m_state = eState::Game;
		break;
	case FunGame::eState::Game: {

		if (m_scene->GetActor("Enemy") == nullptr) {
			m_state = eState::StartLevel;
			m_level++;
			AddPoints(14);
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
				m_lives--;
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
	if (m_state == eState::Title) {
		m_startText->Draw(renderer, 250, 250);
	}

	m_scoreText->Draw(renderer, 40, 40);
	m_lifeText->Draw(renderer, 800, 40);

	m_scene->Draw(renderer);
	hop::g_particleSystem.Draw(renderer);
}
