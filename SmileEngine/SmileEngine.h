#pragma once
#include "SmileEngineLibType.h"
struct SDL_Window;
namespace dae
{
	class SoundSystem;
	class LuaVM;

	struct GameSettings
	{
		int m_WindowWidth;
		int m_WindowHeight;
		SDL_Window* m_pWindow{};
	};

	class SmileEngine
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		SMILEENGINE_ENTRY void Run();

	private:
		void CreateScenes() const;

		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		GameSettings m_GameSettings;
		SoundSystem* m_pSoundSystem;
		LuaVM* m_pLuaVM;
	};
}