#include "SmileEnginePCH.h"
#include "ControlsMenu.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"


dae::ControlsMenu::ControlsMenu(const glm::vec2& pos, SDL_Window* pWindow)
	: UILayer(pos, "ControlsMenu", pWindow)
{

}

void dae::ControlsMenu::Render()
{
	bool isClosable{ false };
	ImGui::Begin("Controls", &isClosable);

	ImGui::SetWindowSize(ImVec2{ 250.f, 100.f });
	ImGui::SetWindowPos(ImVec2{ m_Position.x, m_Position.y });
	ImGui::Text("PlayerDie: A / down");
	ImGui::Text("PlayerIncreaseScore: B / right");
	ImGui::Text("Quit: Y");

	ImGui::End();
}