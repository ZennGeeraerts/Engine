#include "SmileEnginePCH.h"
#include "SDLSoundSystem.h"
#include "SDLSoundSystemImpl.h"

dae::SDLSoundSystem::SDLSoundSystem()
	: m_pImpl{ new SDLSoundSystemImpl{} }
{
	
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	delete m_pImpl;
}

void dae::SDLSoundSystem::Play(const int id, const float volume, const std::string filePath)
{
	m_pImpl->Play(id, volume, filePath);
}

void dae::SDLSoundSystem::Update()
{
	m_pImpl->Update();
}
