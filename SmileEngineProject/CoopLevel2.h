#pragma once
#include <Scene.h>

namespace dae
{
    class CoopLevel2 : public Scene
    {
    public:
        CoopLevel2(const GameSettings& gameSettings);
        void CreateScene() override;
        void OnSceneEnd() override;
    };
}

