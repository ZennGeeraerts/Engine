#pragma once
#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystemImpl;

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() noexcept;
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;

		void Play(const int id, const float volume, const std::string filePath) override;
		void Update();

	private:
		SDLSoundSystemImpl* m_pImpl;
	};
}

