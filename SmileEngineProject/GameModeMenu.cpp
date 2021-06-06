#include "SmileEnginePCH.h"
#include "GameModeMenu.h"
#include "SceneManager.h"
#include "Scene.h"
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
	auto& sceneManager = SceneManager::GetInstance();
	bool isClosable{ false };
	ImGui::Begin("Settings", &isClosable);

	ImGui::SetWindowSize(ImVec2{ 200.f, 150.f });
	ImGui::SetWindowPos(ImVec2{ m_Position.x, m_Position.y });
	if (ImGui::Button("single player"))
	{
		sceneManager.SetScene(1);
		sceneManager.GetScene(1)->CreateScene();
		UIManager::GetInstance().RemoveUILayer("GameModeScene");
	}
	if (ImGui::Button("co-op"))
	{
		sceneManager.SetScene(4);
		sceneManager.GetScene(4)->CreateScene();
		UIManager::GetInstance().RemoveUILayer("GameModeScene");
	}
	if (ImGui::Button("versus"))
	{
		sceneManager.SetScene(7);
		sceneManager.GetScene(7)->CreateScene();
		UIManager::GetInstance().RemoveUILayer("GameModeScene");
	}

	ImGui::End();
}