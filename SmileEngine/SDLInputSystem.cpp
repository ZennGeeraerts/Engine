#include "SmileEnginePCH.h"
#include "SDLInputSystem.h"

void dae::SDLInputSystem::ProcessInput()
{
	m_KeyboardStates = SDL_GetKeyboardState(NULL);
}

bool dae::SDLInputSystem::HandleInput()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

bool dae::SDLInputSystem::IsPressed(SDL_Scancode button) const
{
	return IsDown(button);
}

bool dae::SDLInputSystem::IsDown(SDL_Scancode button) const
{
	if (!m_KeyboardStates)
	{
		return false;
	}

	return m_KeyboardStates[button];
}
