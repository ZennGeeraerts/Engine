#pragma once
#include "Prefab.h"

namespace dae
{
	class TileMap final : public Prefab
	{
	public:
		TileMap(int screenWidth, int screenHeight);
		std::shared_ptr<GameObject> CreatePrefab() override;

	private:
		int m_ScreenWidth;
		int m_ScreenHeight;
	};
}

