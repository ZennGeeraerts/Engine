#pragma once
#include "SoundSystem.h"
#include <queue>
#include <mutex>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		void Play(const int id, const float volume, const std::string filePath) override;
		void Update();

	private:
		void PlaySDLSound(const PlaySound& playSound);

		std::queue<PlaySound> m_PlaySounds;
		std::mutex m_Mutex;
		std::thread m_Thread;
	};
}

