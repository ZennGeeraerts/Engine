#include "SmileEnginePCH.h"
#include "GameModeMenu.h"
#include "SceneManager.h"
#include "UIManager.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

dae::GameModeMenu::GameModeMenu(const glm::vec2& pos)
	: UILayer(pos, "GameModeScene")
{
}

void dae::GameModeMenu::Render()
{
	bool isClosable{ false };
	ImGui::Begin("Settings", &isClosable);

	ImGui::SetWindowSize(ImVec2{ 200.f, 150.f });
	ImGui::SetWindowPos(ImVec2{ m_Position.x, m_Position.y });
	if (ImGui::Button("single player"))
	{
		SceneManager::GetInstance().SetScene(1);
		UIManager::GetInstance().RemoveUILayer("GameModeScene");
	}
	ImGui::Button("co-op");
	ImGui::Button("versus");

	ImGui::End();
}