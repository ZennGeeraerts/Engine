#include "SmileEnginePCH.h"
#include "PlayerUI.h"
#include "GameObject.h"
#include "Subject.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

#include "C_Lives.h"
#include "C_Score.h"

dae::PlayerUI::PlayerUI(const glm::vec2& pos, SDL_Window* pWindow, const std::vector<Subject*>& pSubjects)
	: UILayer(pos, "PlayerUI", pWindow)
	, Observer(pSubjects)
	, m_PlayerName{ "Player" }
	, m_NotifyText{ "" }
	, m_RemainingLives{ 0 }
	, m_Score{ 0 }
{
	for (auto pSubject : pSubjects)
	{
		pSubject->AddObserver(this);
	}
}

void dae::PlayerUI::Render()
{
	bool isClosable{ false };
	ImGui::Begin(m_PlayerName.c_str(), &isClosable);

	ImGui::SetWindowSize(ImVec2{ 200.f, 150.f });
	ImGui::SetWindowPos(ImVec2{ m_Position.x, m_Position.y });
	
	if (m_NotifyText != "")
	{
		ImGui::Text(m_NotifyText.c_str());
	}

	ImGui::Text("Remaining lives:");
	ImGui::Text(std::to_string(m_RemainingLives).c_str());

	ImGui::Text("Score:");
	ImGui::Text(std::to_string(m_Score).c_str());
	
	ImGui::End();
}

void dae::PlayerUI::Notify(GameObject* pGameObject, const std::string& eventName)
{
	if (eventName == "PlayerDied")
	{
		m_NotifyText = eventName;
		m_RemainingLives = pGameObject->GetComponent<C_Lives>()->GetLives();
	}
	else if (eventName == "HealthCreated")
	{
		m_PlayerName = pGameObject->GetName();
	}
	else if (eventName == "LivesUpdated")
	{
		m_RemainingLives = pGameObject->GetComponent<C_Lives>()->GetLives();
	}
	else if (eventName == "ScoreIncrease")
	{
		m_Score = pGameObject->GetComponent<C_Score>()->GetScore();
	}
}
