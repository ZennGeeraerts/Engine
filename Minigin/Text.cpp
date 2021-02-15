#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "Text.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"
#include "ResourceManager.h"

using namespace std;

dae::Text::Text(GameObject* pGameObject)
	: Component(pGameObject)
	, m_NeedsUpdate{ true }
	, m_Text{ "" }
	, m_Font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) }
	, m_pTextureRenderer{ nullptr }
{
	m_pTextureRenderer = pGameObject->GetComponent<TextureRenderer>();
	if (!m_pTextureRenderer)
	{
		std::cerr << "No TextureRenderer found for text" << endl;
	}
}

void dae::Text::Update()
{
	if (m_NeedsUpdate && m_pTextureRenderer)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (pTexture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextureRenderer->SetTexture(std::make_shared<Texture2D>(pTexture));
		m_NeedsUpdate = false;
	}
}

// This implementation uses the "dirty flag" pattern
void dae::Text::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::Text::SetFont(const std::shared_ptr<Font>& font)
{
	m_Font = font;
	m_NeedsUpdate = true;
}
