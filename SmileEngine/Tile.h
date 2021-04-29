#pragma once
#include "Prefab.h"

namespace dae
{
	class Tile final : public Prefab
	{
	public:
		Tile(const glm::vec2& pos);
		std::shared_ptr<GameObject> CreatePrefab() override;
	};
}

