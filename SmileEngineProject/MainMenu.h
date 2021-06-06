#pragma once
#include "Scene.h"

namespace dae
{
    class MainMenu : public Scene
    {
    public:
        MainMenu(const GameSettings& gameSettings);
        void CreateScene() override;
    };
}

