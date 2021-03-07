#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
    class C_Lives final : public Component
    {
    public:
        C_Lives(GameObject* pGameObject);
        ~C_Lives();
        void SetLives(int lives);
        int GetLives() const;
        void RemoveLive();

    private:
        int m_Lives;
    };
}

