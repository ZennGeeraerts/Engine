#pragma once
#include <Scene.h>

namespace dae
{
    class VersusLevel1 final : public Scene
    {
    public:
        VersusLevel1(const GameSettings& gameSettings);
        void CreateScene() override;
        void OnSceneEnd() override;
    };
}

