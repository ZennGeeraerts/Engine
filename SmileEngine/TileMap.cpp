#include "SmileEnginePCH.h"
#include "TileMap.h"
#include "GameObject.h"
#include "Tile.h"

dae::TileMap::TileMap(int screenWidth, int screenHeight)
	: Prefab("TileMap")
	, m_ScreenWidth{ screenWidth }
	, m_ScreenHeight{ screenHeight }
{

}

std::shared_ptr<dae::GameObject> dae::TileMap::CreatePrefab()
{
	const int nrOfRows{ 7 };
	const float tileSize{ 32.f };
	glm::vec2 startRowPos{ m_ScreenWidth / 2 - tileSize / 2, 10.f };
	glm::vec2 tilePos{ startRowPos };

	for (int i{}; i < nrOfRows; ++i)
	{
		for (int j{}; j < (i + 1); ++j)
		{
			Tile* pTile = new Tile{ tilePos };
			m_pGameObject->AddChild(pTile->CreatePrefab().get());
			tilePos.x += tileSize;
		}

		startRowPos.x -= tileSize / 2;
		startRowPos.y += tileSize * 0.75f;
		tilePos = startRowPos;
	}

	return m_pGameObject;
}