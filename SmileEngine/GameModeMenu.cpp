#include "SmileEnginePCH.h"
#include "GameModeMenu.h"
#include <glm/vec2.hpp>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

dae::GameModeMenu::GameModeMenu(const glm::vec2& pos, SDL_Window* pWindow)
	: UILayer(pos, "GameModeScene", pWindow, std::vector<Subject*>{})
{
}

void dae::GameModeMenu::Render()
{
	bool isClosable{ false };
	ImGui::Begin("Settings", &isClosable);

	ImGui::SetWindowSize(ImVec2{ 200.f, 150.f });
	ImGui::SetWindowPos(ImVec2{ m_Position.x, m_Position.y });
	ImGui::Button("single player");
	ImGui::Button("co-op");
	ImGui::Button("versus");

	ImGui::End();
}

void dae::GameModeMenu::Notify(GameObject* pGameObject, const std::string& eventName)
{
	std::cout << eventName << ": " <<  pGameObject << std::endl;
}