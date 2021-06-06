#include "SmileEnginePCH.h"
#include "C_GameManager.h"
#include "C_Health.h"
#include "C_QBertMovement.h"
#include "SmileEngine.h"
#include "SceneManager.h"
#include "Scene.h"
#include "C_Tile.h"
#include "C_Score.h"
#include "C_CoilyController.h"
#include "SmTime.h"

dae::C_GameManager::C_GameManager(GameObject* pGameObject)
	: Component(pGameObject)
	, Observer()
	, m_IsWinCondition{ false }
	, m_ToBeSpawned{}
	, m_RevertTileOnMaxStage{ false }
{

}

void dae::C_GameManager::SetRevertTileOnMaxStage(bool revertTileOnMaxStage)
{
	m_RevertTileOnMaxStage = revertTileOnMaxStage;
}

void dae::C_GameManager::Update()
{
	// Check the win condition
	if (!m_IsWinCondition)
	{
		CheckWinCondition();
	}

	SpawnGameObjects();
	CheckRestart();
}

void dae::C_GameManager::CheckWinCondition()
{
	auto& pSceneManager = SceneManager::GetInstance();
	auto pScene = pSceneManager.GetCurrentScene();
	auto pTileMap = pScene->GetGameObjectByName("TileMap0");
	auto pTiles = pTileMap->GetChildren();
	int nrOfTilesCompleted{ 0 };

	for (size_t i{}; i < pTiles.size(); ++i)
	{
		auto pTileComponent = pTiles[i]->GetComponent<C_Tile>();
		if (pTileComponent->GetStage() == pTileComponent->GetMaxStage())
		{
			++nrOfTilesCompleted;
		}
	}

	if (nrOfTilesCompleted == /*pTiles.size()*/ 3)
	{
		std::vector<GameObject*> pTeleports{};
		pScene->GetGameObjectsWithTag(pTeleports, "Teleport");

		std::vector<GameObject*> pPlayers{};
		pScene->GetGameObjectsWithTag(pPlayers, "Friendly");
		for (auto& pPlayer : pPlayers)
		{
			auto pScore = pPlayer->GetComponent<C_Score>();
			pScore->IncreaseScore(50 * static_cast<int>(pTeleports.size()));
		}

		m_IsWinCondition = true;
		pScene->OnSceneEnd();
	}
}

void dae::C_GameManager::SpawnGameObjects()
{
	const float deltaTime = SmTime::GetInstance().GetDeltaTime();
	std::vector< std::unordered_map<GameObject*, float>::iterator > spawnedIterators{};

	for (auto it = m_ToBeSpawned.begin(); it != m_ToBeSpawned.end(); ++it)
	{
		if (it->second < 0)
		{
			it->first->SetEnabled(true);
			spawnedIterators.push_back(it);
			continue;
		}

		it->second -= deltaTime;
	}

	// Remove spawned objects from map
	for (const auto it : spawnedIterators)
	{
		m_ToBeSpawned.erase(it);
	}
}

void dae::C_GameManager::CheckRestart()
{
	std::vector<GameObject*> pPlayers{};
	auto pScene = SceneManager::GetInstance().GetCurrentScene();
	pScene->GetGameObjectsWithTag(pPlayers, "Friendly");
	if (pPlayers.size() == 0)
	{
		pScene->MarkForRestart();
	}
}

void dae::C_GameManager::Notify(GameObject* pGameObject, const std::string& eventName)
{
	if (eventName == "WalkOutMap")
	{
		auto pHealth = pGameObject->GetComponent<C_Health>();
		if (pHealth)
		{
			pHealth->Kill();
		}
		else
		{
			pGameObject->GetComponent<C_QBertMovement>()->MoveToStartTile(true);

			const float timeToRespawn{ 5.f };
			SpawnOverTime(pGameObject, timeToRespawn);
		}

		if (pGameObject->GetComponent<C_CoilyController>())
		{
			auto pScene = SceneManager::GetInstance().GetCurrentScene();

			std::vector<GameObject*> pPlayers{};
			pScene->GetGameObjectsWithTag(pPlayers, "Friendly");
			for (auto& pPlayer : pPlayers)
			{
				auto pScore = pPlayer->GetComponent<C_Score>();
				pScore->IncreaseScore(500);
			}
		}
	}
	else if (eventName == "PlayerDied")
	{
		std::cout << "Played died" << std::endl;
		pGameObject->GetComponent<C_QBertMovement>()->MoveToStartTile(true);
	}
	else if (eventName == "GameOver")
	{
		std::cout << "Game over" << std::endl;
		pGameObject->MarkForDelete();
	}
	else if (eventName == "UpdateTile")
	{
		const int tileIndex = pGameObject->GetComponent<C_QBertMovement>()->GetCurrentTileIndex();
		auto pScene = SceneManager::GetInstance().GetCurrentScene();
		auto pTileMap = pScene->GetGameObjectByName("TileMap0");
		auto pTileObj = pTileMap->GetChildByIndex(tileIndex);
		auto pTileComp = pTileObj->GetComponent<C_Tile>();

		if (m_RevertTileOnMaxStage && (pTileComp->GetStage() == pTileComp->GetMaxStage()))
		{
			pTileComp->RevertTile();
		}
		else if (pTileComp->UpdateTile())
		{
			// Add score
			auto pScore = pGameObject->GetComponent<C_Score>();
			pScore->IncreaseScore(25);
		}
	}
	else if (eventName == "RevertTile")
	{
		const int tileIndex = pGameObject->GetComponent<C_QBertMovement>()->GetCurrentTileIndex();
		auto pScene = SceneManager::GetInstance().GetCurrentScene();
		auto pTileMap = pScene->GetGameObjectByName("TileMap0");
		auto pTile = pTileMap->GetChildByIndex(tileIndex);
		pTile->GetComponent<C_Tile>()->RevertTile();
	}
}

void dae::C_GameManager::SpawnOverTime(GameObject* pGameObject, float timeToSpawn)
{
	pGameObject->SetEnabled(false);
	m_ToBeSpawned.insert(std::pair<GameObject*, float>{ pGameObject, timeToSpawn });
}
