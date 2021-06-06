#include "SmileEnginePCH.h"
#include "C_WrongwayController.h"
#include "C_QBertMovement.h"
#include "C_Transform.h"
#include "Scene.h"

dae::C_WrongwayController::C_WrongwayController(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pMovement{ nullptr }
{
	m_pMovement = pGameObject->GetComponent<C_QBertMovement>();
	if (!m_pMovement)
	{
		std::cout << "C_WrongwayController > add a QBertMovement component first" << std::endl;
	}

	const int startTile{ 21 };
	auto startPos = m_pGameObject->GetScene()->GetGameObjectByName("TileMap0")->GetChildByIndex(startTile)->GetTransform()->GetPosition();
	startPos.x -= m_pMovement->GetTileSize() * 0.75f;
	startPos.y += m_pMovement->GetTileSize() / 2;
	m_pGameObject->GetTransform()->SetPosition(startPos);

	m_pMovement->SetStartTile(startTile);
	m_pMovement->MoveToStartTile(true);
}

void dae::C_WrongwayController::Update()
{
	if (rand() % 2 == 0)
	{
		m_pMovement->MoveTopRight();
	}
	else
	{
		m_pMovement->MoveRight();
	}
}