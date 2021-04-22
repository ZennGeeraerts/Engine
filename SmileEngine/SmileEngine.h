#pragma once
#include "SmileEngineLibType.h"
struct SDL_Window;
namespace dae
{
	class SoundSystem;
	class LuaVM;

	class SmileEngine
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		SMILEENGINE_ENTRY void Run();

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_pWindow{};
		SoundSystem* m_pSoundSystem;
		LuaVM* m_pLuaVM;
	};
}