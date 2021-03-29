#include "SmileEnginePCH.h"
#include "SDLSoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "SmTime.h"

dae::SDLSoundSystem::SDLSoundSystem()
	: m_PlaySounds{}
	, m_Mutex{}
{
	SDL_Init(SDL_INIT_AUDIO);

	int audioRate{ 22050 };
	Uint16 audioFormat{ AUDIO_S16SYS };
	int audioChannels{ 2 };
	int audioBuffers{ 4096 };

	int result = Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers);
	if (result)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDLSoundSystem: Failed to initialize SDL audio: %s", Mix_GetError());
	}

	m_Thread = std::thread{ 
		[this]()
		{
			this->Update();
		}
	};
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	m_Thread.detach();
}

void dae::SDLSoundSystem::Play(const int id, const float volume, const std::string filePath)
{
	const PlaySound playSound{ id, volume, filePath };
	std::lock_guard<std::mutex> lock{ m_Mutex };
	m_PlaySounds.push(playSound);
}

void dae::SDLSoundSystem::Update()
{
	while (SmTime::GetInstance().GetDoContinue())
	{
		std::lock_guard<std::mutex> lock{ m_Mutex };
		while (!m_PlaySounds.empty())
		{
			PlaySound playSound{ m_PlaySounds.front() };
			m_PlaySounds.pop();
			PlaySDLSound(playSound);
		}
	}
}

void dae::SDLSoundSystem::PlaySDLSound(const PlaySound& playSound)
{
	const auto filePath{ playSound.filePath.c_str() };
	Mix_Chunk* pSoundEffect{ Mix_LoadWAV(filePath) };
	pSoundEffect->volume = static_cast<Uint8>(playSound.volume);

	if (!pSoundEffect)
	{
		std::cerr << "SDLSoundSystem::Play: Failed to create SoundEffect" << std::endl;
		return;
	}

	Mix_PlayChannel(-1, pSoundEffect, 0);
}
