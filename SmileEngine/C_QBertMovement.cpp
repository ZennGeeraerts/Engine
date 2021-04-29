#include "SmileEnginePCH.h"
#include "C_QBertMovement.h"
#include "C_Transform.h"
#include "C_Render.h"
#include "Texture2D.h"
#include "ServiceLocator.h"

dae::C_QBertMovement::C_QBertMovement(GameObject* pGameObject)
	: Component(pGameObject)
	, m_CurrentTileIndex{ 0 }
	, m_pTransform{ pGameObject->GetTransform() }
	, m_pTileMap{ nullptr }
	, m_TileSize{ 0 }
{

}

void dae::C_QBertMovement::SetTileMap(GameObject* pTileMap)
{
	m_pTileMap = pTileMap;
	m_TileSize = pTileMap->GetChildByIndex(0)->GetComponent<C_Render>()->GetTexture()->GetWidth();
}

void dae::C_QBertMovement::MoveBottomLeft()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	m_pGameObject->GetComponent<C_Render>()->SetTexture("qbert_1.png");

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex += currentRow + 1;

	MoveToTile();
}

void dae::C_QBertMovement::MoveTopRight()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	m_pGameObject->GetComponent<C_Render>()->SetTexture("qbert_2.png");

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex -= currentRow;

	MoveToTile();
}

void dae::C_QBertMovement::MoveBottomRight()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	m_pGameObject->GetComponent<C_Render>()->SetTexture("qbert_0.png");

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex += currentRow + 2;

	MoveToTile();
}

void dae::C_QBertMovement::MoveTopLeft()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	m_pGameObject->GetComponent<C_Render>()->SetTexture("qbert_3.png");

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex -= currentRow + 1;

	MoveToTile();
}

int dae::C_QBertMovement::CalculateCurrentRow()
{
	return int((-1 + sqrt(1 + 8 * m_CurrentTileIndex)) / 2);
}

void dae::C_QBertMovement::MoveToTile()
{
	auto pTiles{ m_pTileMap->GetChildren() };
	// TODO: Check if new m_CurrentTileIndex is valid

	auto pos = pTiles[m_CurrentTileIndex]->GetTransform()->GetPosition();
	pos.x += m_TileSize / 4.f;
	pos.y -= m_TileSize / 4.f;
	m_pTransform->SetPosition(pos);

	PlayJumpSound();
}

void dae::C_QBertMovement::PlayJumpSound() const
{
	ServiceLocator::GetSoundSystem().Play(0, 100, "../Data/jump.wav");
}

int dae::C_QBertMovement::GetTileSize() const
{
	return m_TileSize;
}