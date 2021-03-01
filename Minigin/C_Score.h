#pragma once
#include "Component.h"

namespace dae
{
    class Subject;

    class C_Score : public Component
    {
    public:
        C_Score(GameObject* pGameObject);
        ~C_Score();
        int GetScore() const;
        void IncreaseScore(int amount);
        Subject* GetSubject() const;

    private:
        int m_Score;
        Subject* m_pSubject;
    };
}
