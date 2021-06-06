#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
    class C_Lives final : public Component
    {
    public:
        C_Lives(GameObject* pGameObject);
        virtual ~C_Lives() noexcept = default;
        void SetLives(int lives);
        int GetLives() const;
        void RemoveLive();
        Subject* GetSubject() const;

    private:
        int m_Lives;
        Subject* m_pSubject;
    };
}

