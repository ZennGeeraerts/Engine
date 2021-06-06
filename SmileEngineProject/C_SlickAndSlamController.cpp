#include "SmileEnginePCH.h"
#include "C_SlickAndSlamController.h"
#include "C_QBertMovement.h"

dae::C_SlickAndSlamController::C_SlickAndSlamController(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pMovement{ nullptr }
{
	m_pMovement = pGameObject->GetComponent<C_QBertMovement>();
	if (!m_pMovement)
	{
		std::cout << "C_SlickAndSlamController > add a QBertMovement component first" << std::endl;
		return;
	}

	int startTile{ 1 };
	if (rand() % 2 == 0)
	{
		startTile = 2;
	}

	m_pMovement->SetStartTile(startTile);
	m_pMovement->MoveToStartTile(true);
}

void dae::C_SlickAndSlamController::Update()
{
	if (rand() % 2 == 0)
	{
		m_pMovement->MoveBottomLeft();
	}
	else
	{
		m_pMovement->MoveBottomRight();
	}
}
