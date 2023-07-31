#include "InputSystem.h"

namespace hop
{
	InputSystem g_inputSystem;
	bool InputSystem::Initialize()
	{
		int numKeys;
		
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);
		m_keyboardState.resize(numKeys);
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;
		return true;
	}
	void InputSystem::Shutdown()
	{
	}
	void InputSystem::Update()
	{
		// update sdl events
		SDL_Event event;
		SDL_PollEvent(&event);
		// save previous keyboard state
		m_prevKeyboardState = m_keyboardState;
		// get sdl keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		// copy sdl keyboard state to input system keyboard state
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = Vexctor2{ x , y };
		m_prevMouseButtonState = m_mouseButtonState;
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML]
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML]
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]
	}
}