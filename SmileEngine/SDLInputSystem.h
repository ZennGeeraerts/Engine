#pragma once
#include <SDL.h>

namespace dae
{
	class SDLInputSystemImpl;

	class SDLInputSystem final
	{
	public:
		SDLInputSystem();
		~SDLInputSystem() noexcept;

		void ProcessInput();
		bool HandleInput();

		bool IsPressed(SDL_Scancode button) const;
		bool IsDown(SDL_Scancode button) const;

	private:
		SDLInputSystemImpl* m_pImpl;
	};
}

