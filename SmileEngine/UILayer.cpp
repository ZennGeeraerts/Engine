#include "SmileEnginePCH.h"
#include "UILayer.h"

#include <SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

dae::UILayer::UILayer(const glm::vec2& pos, const std::string& name, SDL_Window* pWindow)
	: m_pWindow{ pWindow }
	, m_Name{ name }
	, m_Position{ pos }
{
	
}

dae::UILayer::~UILayer()
{
	
}

std::string dae::UILayer::GetName() const
{
	return m_Name;
}
