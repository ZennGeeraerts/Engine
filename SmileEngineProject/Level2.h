#pragma once
#include "Scene.h"

namespace dae
{
	class Level2 : public Scene
	{
	public:
		Level2(const GameSettings& gameSettings);
		void CreateScene() override;
		void OnSceneEnd() override;
	};
}

