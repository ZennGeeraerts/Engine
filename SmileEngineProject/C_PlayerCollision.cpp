#include "SmileEnginePCH.h"
#include "C_PlayerCollision.h"
#include "SceneManager.h"
#include "Scene.h"
#include "C_Transform.h"
#include "C_Health.h"

dae::C_PlayerCollision::C_PlayerCollision(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pEnemies{}
	, m_pCatchables{}
	, m_IsAIChanged{ true }
{

}

void dae::C_PlayerCollision::Update()
{
	if (m_IsAIChanged)
	{
		auto pScene = SceneManager::GetInstance().GetCurrentScene();
		pScene->GetGameObjectsWithTag(m_pEnemies, "Enemy");
		pScene->GetGameObjectsWithTag(m_pCatchables, "Catchable");
		m_IsAIChanged = false;
	}

	const auto playerPosition = m_pGameObject->GetTransform()->GetPosition();
	const float distanceOffset{ 5.f };

	for (auto& pEnemy : m_pEnemies)
	{
		if (!pEnemy->GetIsEnabled())
		{
			continue;
		}

		const auto enemyPosition = pEnemy->GetTransform()->GetPosition();

		if (glm::distance(enemyPosition, playerPosition) < distanceOffset)
		{
			auto pHealth = m_pGameObject->GetComponent<C_Health>();
			if (pHealth)
			{
				pHealth->Kill();
			}
		}
	}

	for (auto& pCatchable : m_pCatchables)
	{
		if (!pCatchable->GetIsEnabled())
		{
			continue;
		}

		const auto catchablePosition = pCatchable->GetTransform()->GetPosition();

		if (glm::distance(catchablePosition, playerPosition) < distanceOffset)
		{
			pCatchable->MarkForDelete();
			m_IsAIChanged = true;
		}
	}
}
