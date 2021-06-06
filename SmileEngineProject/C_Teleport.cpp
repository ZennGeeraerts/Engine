#include "SmileEnginePCH.h"
#include "C_Teleport.h"
#include "C_QBertMovement.h"
#include "SceneManager.h"
#include "Scene.h"
#include "C_Transform.h"
#include "C_Render.h"
#include "SmTime.h"
#include "C_CoilyController.h"

dae::C_Teleport::C_Teleport(GameObject* pGameObject)
	: Component(pGameObject)
	, m_ConnectedTile{ 0 }
	, m_MovementDirection{ C_QBertMovement::MovementDirection::eTopLeft }
	, m_pRenderComponent{ nullptr }
	, m_TexturePaths{}
	, m_TextureIndex{ 0 }
	, m_RotationTime{ m_MaxRotationTime }
	, m_pPlayer{ nullptr }
	, m_StartPosition{}
	, m_DestPosition{}
{
	m_pRenderComponent = m_pGameObject->GetComponent<C_Render>();
	if (!m_pRenderComponent)
	{
		std::cout << "C_Teleport > Add a render component first" << std::endl;
	}

}

void dae::C_Teleport::SetConnectedTile(int connectedTile, C_QBertMovement::MovementDirection movementDir)
{
	m_ConnectedTile = connectedTile;
	m_MovementDirection = movementDir;

	auto& sceneManager = SceneManager::GetInstance();
	auto pTileMap = sceneManager.GetCurrentScene()->GetGameObjectByName("TileMap0");
	auto pTile = pTileMap->GetChildByIndex(m_ConnectedTile);
	m_StartPosition = pTile->GetTransform()->GetPosition();
	const float tileSize{ 32.f };

	switch (m_MovementDirection)
	{
	case dae::C_QBertMovement::MovementDirection::eBottomLeft:
		m_StartPosition.x -= tileSize / 2 / 2;
		m_StartPosition.y -= tileSize / 2 * 0.75f;
		break;
	case dae::C_QBertMovement::MovementDirection::eTopRight:
		m_StartPosition.x += (tileSize / 2 + tileSize) / 2;
		m_StartPosition.y -= tileSize / 2 * 0.75f;
		break;
	case dae::C_QBertMovement::MovementDirection::eBottomRight:
		m_StartPosition.x += (tileSize / 2 + tileSize) / 2;
		m_StartPosition.y += tileSize / 2 * 0.75f;
		break;
	case dae::C_QBertMovement::MovementDirection::eTopLeft:
		m_StartPosition.x -= tileSize / 2 / 2;
		m_StartPosition.y -= tileSize / 2 * 0.75f;
		break;
	}

	m_pGameObject->GetTransform()->SetPosition(m_StartPosition);
	m_DestPosition = pTileMap->GetChildByIndex(0)->GetTransform()->GetPosition();
	m_DestPosition.y -= 20.f;
}

void dae::C_Teleport::SetTexturePaths(const std::vector<std::string>& texturePaths)
{
	m_TexturePaths = texturePaths;
}

void dae::C_Teleport::Update()
{
	if (!m_pRenderComponent || m_TexturePaths.empty())
	{
		return;
	}

	auto& time = SmTime::GetInstance();
	m_RotationTime -= time.GetDeltaTime();
	if (m_RotationTime < 0)
	{
		++m_TextureIndex;
		if (m_TextureIndex == static_cast<int>(m_TexturePaths.size()))
		{
			m_TextureIndex = 0;
		}

		m_pRenderComponent->SetTexture(m_TexturePaths[m_TextureIndex]);
		m_RotationTime = m_MaxRotationTime;
	}

	auto pTransform = m_pGameObject->GetTransform();
	auto currentPos = pTransform->GetPosition();

	if (m_pPlayer)
	{
		// Check if dest target is reached
		if (glm::distance(m_DestPosition, currentPos) < 0.1f)
		{
			m_pPlayer = nullptr;
			return;
		}

		glm::vec3 direction{ glm::normalize(m_DestPosition - currentPos) };
		direction *= m_MoveSpeed * time.GetDeltaTime();
		currentPos += direction;
		pTransform->SetPosition(currentPos);
		m_pPlayer->GetTransform()->SetPosition(currentPos);
	}
	else
	{
		// Check if start pos is reached
		if (glm::distance(m_StartPosition, currentPos) < 0.1f)
		{
			return;
		}

		// Move back to start pos
		/*glm::vec3 direction{ glm::normalize(m_StartPosition - currentPos) };
		direction *= m_MoveSpeed * time.GetDeltaTime();
		currentPos += direction;
		pTransform->SetPosition(currentPos);*/

		m_pGameObject->MarkForDelete();
	}
}

void dae::C_Teleport::Teleport(dae::GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
	auto pCoily = SceneManager::GetInstance().GetCurrentScene()->GetGameObjectByName("Coily");
	if (pCoily)
	{
		auto pCoilyController = pCoily->GetComponent<C_CoilyController>();
		pCoilyController->OnPlayerTeleport(this);
	}
}

int dae::C_Teleport::GetConnectedTile() const
{
	return m_ConnectedTile;
}

dae::C_QBertMovement::MovementDirection dae::C_Teleport::GetMovementDirection() const
{
	return m_MovementDirection;
}