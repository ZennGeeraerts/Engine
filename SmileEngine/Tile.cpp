#include "SmileEnginePCH.h"
#include "Tile.h"
#include "GameObject.h"

#include "C_Transform.h"
#include "C_Render.h"
#include "C_Tile.h"

dae::Tile::Tile(const glm::vec2& pos)
	: Prefab("Tile")
{
	C_Transform* pTransform = m_pGameObject->GetComponent<C_Transform>();
	pTransform->SetPosition(pos.x, pos.y, 1.0f);
}

std::shared_ptr<dae::GameObject> dae::Tile::CreatePrefab()
{
	m_pGameObject->AddComponent<C_Render>();
	m_pGameObject->AddComponent<C_Tile>();
	return m_pGameObject;
}
