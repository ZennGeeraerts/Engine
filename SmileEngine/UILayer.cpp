#include "MiniginPCH.h"
#include "UILayer.h"
#include "Subject.h"

#include <SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

dae::UILayer::UILayer(const glm::vec2& pos, const std::string& name, SDL_Window* pWindow, const std::vector<Subject*> pSubjects)
	: Observer(pSubjects)
	, m_pWindow{ pWindow }
	, m_Name{ name }
	, m_Position{ pos }
{
	for (auto pSubject : pSubjects)
	{
		pSubject->AddObserver(this);
	}
}

dae::UILayer::~UILayer()
{
	
}

std::string dae::UILayer::GetName() const
{
	return m_Name;
}
