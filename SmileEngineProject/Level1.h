#pragma once
#include "Scene.h"

namespace dae
{
    class Level1 final : public Scene
    {
    public:
        Level1(const GameSettings& gameSettings);
        void CreateScene() override;
        void OnSceneEnd() override;
    };
}

