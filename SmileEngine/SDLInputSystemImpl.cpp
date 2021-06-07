#include "SmileEnginePCH.h"
#include "SDLInputSystemImpl.h"

void dae::SDLInputSystemImpl::ProcessInput()
{
	m_KeyboardStates = SDL_GetKeyboardState(NULL);
}

bool dae::SDLInputSystemImpl::HandleInput()
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

bool dae::SDLInputSystemImpl::IsPressed(SDL_Scancode button) const
{
	return IsDown(button);
}

bool dae::SDLInputSystemImpl::IsDown(SDL_Scancode button) const
{
	if (!m_KeyboardStates)
	{
		return false;
	}

	return m_KeyboardStates[button];
}