#pragma once
#include <Scene.h>

namespace dae
{
	class CoopLevel3 : public Scene
	{
	public:
		CoopLevel3(const GameSettings& gameSettings);
		void CreateScene() override;
		void OnSceneEnd() override;
	};
}
