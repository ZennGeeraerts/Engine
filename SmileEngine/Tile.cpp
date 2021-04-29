#include "SmileEnginePCH.h"
#include "Tile.h"
#include "GameObject.h"

#include "C_Transform.h"
#include "C_Render.h"

dae::Tile::Tile(const glm::vec2& pos)
	: Prefab("Tile")
{
	C_Transform* pTransform = m_pGameObject->GetComponent<C_Transform>();
	pTransform->SetPosition(pos.x, pos.y, 1.0f);
}

std::shared_ptr<dae::GameObject> dae::Tile::CreatePrefab()
{
	C_Render* pRender = m_pGameObject->AddComponent<C_Render>();
	pRender->SetTexture("tile_blue.png");
	return m_pGameObject;
}
