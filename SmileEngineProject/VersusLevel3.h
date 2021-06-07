#pragma once
#include <Scene.h>

namespace dae
{
    class VersusLevel3 final : public Scene
    {
    public:
        VersusLevel3(const GameSettings& gameSettings);
        void CreateScene() override;
        void OnSceneEnd() override;
    };
}

