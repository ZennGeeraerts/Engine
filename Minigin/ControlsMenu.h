#pragma once
#include "UILayer.h"

namespace dae
{
    class ControlsMenu : public UILayer
    {
    public:
        ControlsMenu(const glm::vec2& pos, SDL_Window* pWindow);
        void Render() override;
        void Notify(GameObject* pGameObject, const std::string& eventName) override;

    private:
    };
}

