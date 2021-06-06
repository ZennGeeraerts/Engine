#pragma once
#include <Scene.h>

namespace dae
{
    class CoopLevel1 final : public Scene
    {
    public:
        CoopLevel1(const GameSettings& gameSettings);
        void CreateScene() override;
        void OnSceneEnd() override;
    };
}

