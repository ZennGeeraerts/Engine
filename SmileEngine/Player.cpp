#include "SmileEnginePCH.h"
#include "Player.h"
#include "GameObject.h"
#include <SDL.h>

#include "InputManager.h"
#include "InputCommands.h"

#include "UIManager.h"
#include "PlayerUI.h"

#include "SceneManager.h"
#include "Scene.h"

#include "C_Health.h"
#include "C_Lives.h"
#include "C_Score.h"
#include "C_Render.h"
#include "C_Transform.h"
#include "C_QBertMovement.h"

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

	auto pRender = m_pGameObject->AddComponent<C_Render>();
	pRender->SetTexture("qbert_0.png");

	std::shared_ptr<Scene> pScene = SceneManager::GetInstance().GetScene(0);
	GameObject* pTileMap = pScene->GetGameObjectByName("TileMap0");;
	auto pMovement = m_pGameObject->AddComponent<C_QBertMovement>();
	pMovement->SetTileMap(pTileMap);
	
	GameObject* pStartTile = pTileMap->GetChildByIndex(0);
	auto pos = pStartTile->GetTransform()->GetPosition();
	const int tileSize{ pMovement->GetTileSize() };
	pos.x += tileSize / 4.f;
	pos.y -= tileSize / 4.f;
	m_pGameObject->GetComponent<C_Transform>()->SetPosition(pos);

	// input
	inputManager.AddInputAction(m_DieButton, new PlayerDie{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(m_IncreaseScoreButton, new ScoreIncrease{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonY, new Quit{ InputManager::InputKeyAction::ePressed });

	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonLeft, new MoveBottomLeft{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonUp, new MoveTopLeft{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonRight, new MoveTopRight{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonDown, new MoveBottomRight{ m_pGameObject.get(), InputManager::InputKeyAction::ePressed });

	// UI
	std::vector<Subject*> pSubjects{ pHealth->GetSubject(), pScore->GetSubject() };
	UIManager::GetInstance().AddUILayer(new PlayerUI{ m_UIPosition, pSubjects });

	return m_pGameObject;
}
