#include "SmileEnginePCH.h"
#include "Player.h"
#include "GameObject.h"
#include <SDL.h>

#include "InputManager.h"
#include "InputCommands.h"

#include "UIManager.h"
#include "PlayerUI.h"

#include "C_Health.h"
#include "C_Lives.h"
#include "C_Score.h"

dae::Player::Player(const glm::vec2& uiPos, SDL_Window* pWindow, XBoxController::ControllerButton dieButton, XBoxController::ControllerButton increaseScoreButton)
	: Prefab("Player")
	, m_DieButton{ dieButton }
	, m_IncreaseScoreButton{ increaseScoreButton }
	, m_pWindow{ pWindow }
	, m_UIPosition{ uiPos }
{
	
}

std::shared_ptr<dae::GameObject> dae::Player::CreatePrefab()
{
	auto& inputManager{ InputManager::GetInstance() };

	auto pLives = m_pGameObject->AddComponent<C_Lives>();
	pLives->SetLives(3);

	auto pHealth = m_pGameObject->AddComponent<C_Health>();
	pHealth->SetHealth(1);

	auto pScore = m_pGameObject->AddComponent<C_Score>();

	inputManager.AddInputAction(m_DieButton, new PlayerDie{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(m_IncreaseScoreButton, new ScoreIncrease{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonY, new Quit{ InputManager::InputKeyAction::ePressed });

	std::vector<Subject*> pSubjects{ pHealth->GetSubject(), pScore->GetSubject() };
	UIManager::GetInstance().AddUILayer(new PlayerUI{ m_UIPosition, m_pWindow, pSubjects });

	return m_pGameObject;
}
