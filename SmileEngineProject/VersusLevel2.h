#pragma once
#include <Scene.h>

namespace dae
{
	class VersusLevel2 : public Scene
	{
	public:
		VersusLevel2(const GameSettings& gameSettings);
		void CreateScene() override;
		void OnSceneEnd() override;
	};
}