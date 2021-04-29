#include "SmileEnginePCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
	: m_Texture{ texture }
	, m_Width{}
	, m_Heigth{}
{
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Width, &m_Heigth);
}

int dae::Texture2D::GetWidth() const
{
	return m_Width;
}

int dae::Texture2D::GetHeight() const
{
	return m_Heigth;
}