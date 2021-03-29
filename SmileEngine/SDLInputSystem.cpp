#include "SmileEnginePCH.h"
#include "SDLInputSystem.h"

void dae::SDLInputSystem::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_KeyboardStates = SDL_GetKeyboardState(NULL);
	}
}

bool dae::SDLInputSystem::HandleInput()
{
	/*SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			return OnKeyDown(event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			return OnKeyReleased(event.key.keysym.sym);
			break;
		}
	}*/

	return true;
}

bool dae::SDLInputSystem::OnKeyDown(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
	case SDLK_w:

		break;
	}

	return true;
}

bool dae::SDLInputSystem::OnKeyReleased(SDL_Keycode )
{
	/*switch (keyCode)
	{
		break;
	}*/

	return true;
}

//bool dae::SDLInputSystem::IsPressed()
//{
//	
//}

bool dae::SDLInputSystem::IsDown(SDL_Scancode button)
{
	if (!m_KeyboardStates)
	{
		return false;
	}

	return m_KeyboardStates[button];
}
