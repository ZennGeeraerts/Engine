#include "SmileEnginePCH.h"
#include "SDLInputSystem.h"
#include "SDLInputSystemImpl.h"

dae::SDLInputSystem::SDLInputSystem()
	: m_pImpl{ new SDLInputSystemImpl{} }
{

}

dae::SDLInputSystem::~SDLInputSystem()
{
	delete m_pImpl;
}

void dae::SDLInputSystem::ProcessInput()
{
	m_pImpl->ProcessInput();
}

bool dae::SDLInputSystem::HandleInput()
{
	return m_pImpl->HandleInput();
}

bool dae::SDLInputSystem::IsPressed(SDL_Scancode button) const
{
	return m_pImpl->IsPressed(button);
}

bool dae::SDLInputSystem::IsDown(SDL_Scancode button) const
{
	return m_pImpl->IsDown(button);
}
