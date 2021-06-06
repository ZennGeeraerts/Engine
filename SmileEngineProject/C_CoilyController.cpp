#include "SmileEnginePCH.h"
#include "C_CoilyController.h"
#include "C_QBertMovement.h"
#include "C_Transform.h"
#include "C_Teleport.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Input.h"

dae::C_CoilyController::C_CoilyController(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pMovement{ nullptr }
	, m_HasReachedBottom{ false }
	, m_NrOfRows{ 0 }
	, m_pTeleport{ nullptr }
	, m_IsInputControlled{ false }
{
	m_pMovement = pGameObject->GetComponent<C_QBertMovement>();
	if (!m_pMovement)
	{
		std::cout << "C_CoilyController > add a QBertMovement component first" << std::endl;
	}

	if (rand() % 2 == 0)
	{
		m_pMovement->SetStartTile(1);
	}
	else
	{
		m_pMovement->SetStartTile(2);
	}

	m_pMovement->MoveToStartTile(true);
}

void dae::C_CoilyController::SetNrOfRows(int nrOfRows)
{
	m_NrOfRows = nrOfRows;
}

void dae::C_CoilyController::SetIsInputControlled(bool isInputControlled)
{
	m_IsInputControlled = isInputControlled;
}

void dae::C_CoilyController::Update()
{
	if (!m_HasReachedBottom)
	{
		MoveToBottom();
	}
	else if (!m_IsInputControlled)
	{
		ChasePlayer();
	}
}

void dae::C_CoilyController::MoveToBottom()
{
	if (rand() % 2 == 0)
	{
		m_pMovement->MoveBottomLeft();
	}
	else
	{
		m_pMovement->MoveBottomRight();
	}

	if (m_pMovement->CalculateCurrentRow() == (m_NrOfRows - 1))
	{
		m_HasReachedBottom = true;

		if (m_IsInputControlled)
		{
			auto& inputManager{ InputManager::GetInstance() };
			inputManager.AddInputAction(SDL_SCANCODE_A, new MoveBottomLeft{ m_pGameObject, InputManager::InputKeyAction::ePressed });
			inputManager.AddInputAction(SDL_SCANCODE_W, new MoveTopLeft{ m_pGameObject, InputManager::InputKeyAction::ePressed });
			inputManager.AddInputAction(SDL_SCANCODE_D, new MoveTopRight{ m_pGameObject, InputManager::InputKeyAction::ePressed });
			inputManager.AddInputAction(SDL_SCANCODE_S, new MoveBottomRight{ m_pGameObject, InputManager::InputKeyAction::ePressed });
		}
	}
}

void dae::C_CoilyController::ChasePlayer()
{
	auto pScene = SceneManager::GetInstance().GetCurrentScene();
	std::vector<GameObject*> pPlayers{};
	pScene->GetGameObjectsWithTag(pPlayers, "Friendly");

	if (pPlayers.empty())
	{
		return;
	}

	// find nearest player
	GameObject* pNearestPlayer{ pPlayers[0] };
	auto coilyPos = m_pGameObject->GetTransform()->GetPosition();
	for (auto pPlayer : pPlayers)
	{
		auto playerPos = pPlayer->GetTransform()->GetPosition();
		auto nearestPos = pNearestPlayer->GetTransform()->GetPosition();
		if (glm::distance(coilyPos, playerPos) < glm::distance(coilyPos, nearestPos))
		{
			pNearestPlayer = pPlayer;
		}
	}

	// Chase
	auto dir = pNearestPlayer->GetTransform()->GetPosition() - coilyPos;

	if (m_pTeleport)
	{
		const int connectedTile = m_pTeleport->GetConnectedTile();
		auto pTileMap = SceneManager::GetInstance().GetCurrentScene()->GetGameObjectByName("TileMap0");

		if ((connectedTile >= 0) && (connectedTile < pTileMap->GetChildren().size()))
		{
			dir = pTileMap->GetChildByIndex(connectedTile)->GetTransform()->GetPosition() - coilyPos;

			if ((glm::length(dir) < 16.f) && m_pMovement->GetHasDestPosReached())
			{
				auto movementDirection = m_pTeleport->GetMovementDirection();

				switch (movementDirection)
				{
				case dae::C_QBertMovement::MovementDirection::eBottomLeft:
					m_pMovement->MoveBottomLeft();
					break;
				case dae::C_QBertMovement::MovementDirection::eTopRight:
					m_pMovement->MoveTopRight();
					break;
				case dae::C_QBertMovement::MovementDirection::eBottomRight:
					m_pMovement->MoveBottomRight();
					break;
				case dae::C_QBertMovement::MovementDirection::eTopLeft:
					m_pMovement->MoveTopLeft();
					break;
				}

				m_pTeleport = nullptr;
				return;
			}
		}
	}

	if (glm::length(dir) < 0.1f)
	{
		return;
	}
	
	if (dir.x > 0)
	{
		if (dir.y < 0)
		{
			m_pMovement->MoveTopRight();
		}
		else
		{
			m_pMovement->MoveBottomRight();
		}
	}
	else
	{
		if (dir.y < 0)
		{
			m_pMovement->MoveTopLeft();
		}
		else
		{
			m_pMovement->MoveBottomLeft();
		}
	}
}

void dae::C_CoilyController::OnPlayerTeleport(C_Teleport* pTeleport)
{
	if (m_HasReachedBottom)
	{
		m_pTeleport = pTeleport;
	}
}