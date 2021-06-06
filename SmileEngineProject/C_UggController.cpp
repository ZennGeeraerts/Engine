#include "SmileEnginePCH.h"
#include "C_UggController.h"
#include "C_QBertMovement.h"
#include "C_Transform.h"
#include "Scene.h"

dae::C_UggController::C_UggController(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pMovement{ nullptr }
{
	m_pMovement = pGameObject->GetComponent<C_QBertMovement>();
	if (!m_pMovement)
	{
		std::cout << "C_UggController > add a QBertMovement component first" << std::endl;
		return;
	}

	const int startTile{ 27 };
	auto startPos = m_pGameObject->GetScene()->GetGameObjectByName("TileMap0")->GetChildByIndex(startTile)->GetTransform()->GetPosition();
	startPos.x += m_pMovement->GetTileSize() * 0.75f;
	startPos.y += m_pMovement->GetTileSize() / 2;
	m_pGameObject->GetTransform()->SetPosition(startPos);

	m_pMovement->SetStartTile(startTile);
	m_pMovement->MoveToStartTile(false);
}


void dae::C_UggController::Update()
{
	if (rand() % 2 == 0)
	{
		m_pMovement->MoveTopLeft();
	}
	else
	{
		m_pMovement->MoveLeft();
	}
}