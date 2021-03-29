#pragma once
#include <SDL.h>

namespace dae
{
	class SDLInputSystem final
	{
	public:
		void ProcessInput();
		bool HandleInput();

		//bool IsPressed();
		bool IsDown(SDL_Scancode button);
		//bool IsReleased();

	private:
		bool OnKeyDown(SDL_Keycode keyCode);
		bool OnKeyReleased(SDL_Keycode keyCode);

		const Uint8* m_KeyboardStates{ nullptr };
	};
}

