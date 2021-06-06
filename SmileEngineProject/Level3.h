#pragma once
#include <Scene.h>

namespace dae
{
	class Level3 : public Scene
	{
	public:
		Level3(const GameSettings& gameSettings);
		void CreateScene() override;
		void OnSceneEnd() override;
	};
}

