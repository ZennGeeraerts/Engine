#pragma once
#include "UILayer.h"

namespace dae
{
    class ControlsMenu : public UILayer
    {
    public:
        ControlsMenu(const glm::vec2& pos);
        void Render() override;

    private:
    };
}

