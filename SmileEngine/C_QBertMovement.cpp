#include "SmileEnginePCH.h"
#include "C_QBertMovement.h"
#include "C_Transform.h"
#include "C_Render.h"
#include "Texture2D.h"
#include "ServiceLocator.h"
#include "SmTime.h"
#include "Subject.h"
#include "C_Teleport.h"

dae::C_QBertMovement::C_QBertMovement(GameObject* pGameObject)
	: Component(pGameObject)
	, m_CurrentTileIndex{ 0 }
	, m_pTransform{ pGameObject->GetTransform() }
	, m_pTileMap{ nullptr }
	, m_TileSize{ 0 }
	, m_HasDestPosReached{ true }
	, m_pSubject{ new Subject{} }
	, m_StartTile{ 0 }
	, m_TileChange{ TileChange::eNone }
	, m_pTeleports{}
{
	
}

void dae::C_QBertMovement::SetTileMap(GameObject* pTileMap)
{
	m_pTileMap = pTileMap;
	m_TileSize = pTileMap->GetChildByIndex(0)->GetComponent<C_Render>()->GetTexture()->GetWidth();
}

void dae::C_QBertMovement::SetTexturePaths(const std::vector<std::string>& texturePaths)
{
	m_TexturePaths = texturePaths;
}

void dae::C_QBertMovement::SetStartTile(int tileIndex)
{
	m_StartTile = tileIndex;
}

void dae::C_QBertMovement::SetTileChange(TileChange tileChange)
{
	m_TileChange = tileChange;
}

void dae::C_QBertMovement::SetTeleports(const std::vector<C_Teleport*> pTeleports)
{
	m_pTeleports = pTeleports;
}

void dae::C_QBertMovement::Update()
{
	if (!m_HasDestPosReached)
	{
		MoveToTile();
	}
}

void dae::C_QBertMovement::MoveToStartTile(bool teleport)
{
	SetTile(m_StartTile, teleport);
}

void dae::C_QBertMovement::SetTile(int tileIndex, bool teleport)
{
	m_CurrentTileIndex = tileIndex;
	m_HasDestPosReached = false;

	if (teleport)
	{
		auto pTiles{ m_pTileMap->GetChildren() };

		auto destPos = pTiles[m_CurrentTileIndex]->GetTransform()->GetPosition();
		destPos.x += m_TileSize / 4.f;
		destPos.y -= m_TileSize / 4.f;

		m_pGameObject->GetTransform()->SetPosition(destPos);
		m_HasDestPosReached = true;
	}
}

void dae::C_QBertMovement::MoveBottomLeft()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	if (!m_HasDestPosReached)
	{
		return;
	}

	if (m_TexturePaths.size() > 1)
	{
		m_pGameObject->GetComponent<C_Render>()->SetTexture(m_TexturePaths[1]);
	}
	else
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > Couldn't set the right texture" << std::endl;
		return;
	}

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex += currentRow + 1;
	
	Move(currentRow);
}

void dae::C_QBertMovement::MoveTopRight()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	if (!m_HasDestPosReached)
	{
		return;
	}

	if (m_TexturePaths.size() > 2)
	{
		m_pGameObject->GetComponent<C_Render>()->SetTexture(m_TexturePaths[2]);
	}
	else
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > Couldn't set the right texture" << std::endl;
		return;
	}

	if (CheckTeleport(MovementDirection::eTopRight))
	{
		return;
	}

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex -= currentRow;
	
	Move(currentRow);
}

void dae::C_QBertMovement::MoveBottomRight()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	if (!m_HasDestPosReached)
	{
		return;
	}

	if (m_TexturePaths.size() > 0)
	{
		m_pGameObject->GetComponent<C_Render>()->SetTexture(m_TexturePaths[0]);
	}
	else
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > Couldn't set the right texture" << std::endl;
		return;
	}

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex += currentRow + 2;

	Move(currentRow);
}

void dae::C_QBertMovement::MoveTopLeft()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	if (!m_HasDestPosReached)
	{
		return;
	}

	if (m_TexturePaths.size() > 3)
	{
		m_pGameObject->GetComponent<C_Render>()->SetTexture(m_TexturePaths[3]);
	}
	else
	{
		std::cout << "C_QBertMovement::MoveBottomLeft() > Couldn't set the right texture" << std::endl;
		return;
	}

	if (CheckTeleport(MovementDirection::eTopLeft))
	{
		return;
	}

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex -= currentRow + 1;
	
	Move(currentRow);
}

void dae::C_QBertMovement::Move(int currentRow)
{
	CheckValidTile(currentRow);
	m_HasDestPosReached = false;
	PlayJumpSound();
}

bool dae::C_QBertMovement::CheckTeleport(MovementDirection movementDir)
{
	for (auto pTeleport : m_pTeleports)
	{
		if ((pTeleport->GetMovementDirection() == movementDir) && (pTeleport->GetConnectedTile() == m_CurrentTileIndex))
		{
			auto destPos = pTeleport->GetGameObject()->GetTransform()->GetPosition();
			m_pGameObject->GetTransform()->SetPosition(destPos);
			m_CurrentTileIndex = m_StartTile;
			m_HasDestPosReached = false;
			pTeleport->Teleport(m_pGameObject);
			return true;
		}
	}

	return false;
}

void dae::C_QBertMovement::MoveLeft()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	if (!m_HasDestPosReached)
	{
		return;
	}

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex -= 1;
	if (CalculateCurrentRow() != currentRow)
	{
		m_pSubject->Notify(m_pGameObject, "WalkOutMap");
	}
	else
	{
		m_HasDestPosReached = false;
	}

	if (m_TexturePaths.size() > 0)
	{
		m_pGameObject->GetComponent<C_Render>()->SetTexture(m_TexturePaths[0]);
	}
	else
	{
		std::cout << "C_QBertMovement::MoveLeft() > Couldn't set the right texture" << std::endl;
		return;
	}

	PlayJumpSound();
}

void dae::C_QBertMovement::MoveRight()
{
	if (!m_pTileMap)
	{
		std::cout << "C_QBertMovement::MoveLeft() > m_pTileMap is a nullptr, set the tile map first" << std::endl;
		return;
	}

	if (!m_HasDestPosReached)
	{
		return;
	}

	const int currentRow{ CalculateCurrentRow() };
	m_CurrentTileIndex += 1;
	if (CalculateCurrentRow() != currentRow)
	{
		m_pSubject->Notify(m_pGameObject, "WalkOutMap");
	}
	else
	{
		m_HasDestPosReached = false;
	}

	if (m_TexturePaths.size() > 0)
	{
		m_pGameObject->GetComponent<C_Render>()->SetTexture(m_TexturePaths[0]);
	}
	else
	{
		std::cout << "C_QBertMovement::MoveRight() > Couldn't set the right texture" << std::endl;
		return;
	}

	PlayJumpSound();
}

int dae::C_QBertMovement::CalculateCurrentRow() const
{
	return int((-1 + sqrt(1 + 8 * m_CurrentTileIndex)) / 2);
}

void dae::C_QBertMovement::CheckValidTile(int previousRow)
{
	// Check if new m_CurrentTileIndex is valid
	const int currentRow{ CalculateCurrentRow() };
	int rowDifference{ currentRow - previousRow };
	if (((rowDifference != 1) && (rowDifference != -1)) 
		|| (m_CurrentTileIndex < 0) || (m_CurrentTileIndex >= m_pTileMap->GetChildren().size()))
	{
		m_pSubject->Notify(m_pGameObject, "WalkOutMap");
	}
	else
	{
		switch (m_TileChange)
		{
		case dae::C_QBertMovement::TileChange::eUpdate:
			m_pSubject->Notify(m_pGameObject, "UpdateTile");
			break;
		case dae::C_QBertMovement::TileChange::eRevert:
			m_pSubject->Notify(m_pGameObject, "RevertTile");
			break;
		}
		m_HasDestPosReached = false;
	}
}

void dae::C_QBertMovement::MoveToTile()
{
	auto pTiles{ m_pTileMap->GetChildren() };

	auto currentPos = m_pTransform->GetPosition();

	auto destPos = pTiles[m_CurrentTileIndex]->GetTransform()->GetPosition();
	destPos.x += m_TileSize / 4.f;
	destPos.y -= m_TileSize / 4.f;

	if (glm::distance(currentPos, destPos) < 1.f)
	{
		currentPos = destPos;
		m_HasDestPosReached = true;
	}
	else
	{
		glm::vec3 moveDirection{ destPos - currentPos };
		moveDirection.z = 0;
		moveDirection = glm::normalize(moveDirection);
		currentPos += moveDirection * m_MoveSpeed * SmTime::GetInstance().GetDeltaTime();
	}

	m_pTransform->SetPosition(currentPos);
}

void dae::C_QBertMovement::PlayJumpSound() const
{
	ServiceLocator::GetSoundSystem().Play(0, 100, "../Data/jump.wav");
}

int dae::C_QBertMovement::GetTileSize() const
{
	return m_TileSize;
}

dae::Subject* dae::C_QBertMovement::GetSubject() const
{
	return m_pSubject;
}

int dae::C_QBertMovement::GetCurrentTileIndex() const
{
	return m_CurrentTileIndex;
}

bool dae::C_QBertMovement::GetHasDestPosReached() const
{
	return m_HasDestPosReached;
}