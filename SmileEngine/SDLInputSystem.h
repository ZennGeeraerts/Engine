#pragma once
#include <SDL.h>

namespace dae
{
	class SDLInputSystem final
	{
	public:
		void ProcessInput();
		bool HandleInput();

		bool IsPressed(SDL_Scancode button) const;
		bool IsDown(SDL_Scancode button) const;

	private:
		const Uint8* m_KeyboardStates{ nullptr };
	};
}

