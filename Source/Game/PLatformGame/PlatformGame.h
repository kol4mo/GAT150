#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Framework/Event/EventManager.h"

class PlatformGame : public hop::Game, hop::IEventListener {
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadstart,
		PlayerDead,
		GameOverstart,
		GameOver
	};


public:

	// Inherited via Game
	virtual bool Initialize() override;

	virtual void shutdown() override;

	virtual void update(float dt) override;

	virtual void draw(hop::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
	void OnAddPoints(const hop::Event& event);
	void OnPlayerDead(const hop::Event& event);
	eState getState() { return m_state; }

private:
	eState m_state = eState::Title;
	int m_level;
	int difcur;
	float m_stateTimer;
};