#pragma once
#include <memory>

namespace hop
{
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;
		virtual bool Initialize() = 0;
		virtual void shutdown() = 0;

		virtual void update(float dt) = 0;
		virtual void draw(Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }

		int GetLives() const { return m_lives; }
		void SetLives(int live) { m_lives = live; }

	protected:
		std::unique_ptr<class Scene> m_scene;

		int m_score = 0;
		int m_lives = 0;
	};
}