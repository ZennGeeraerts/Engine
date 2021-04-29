#pragma once
#include "Component.h"

namespace dae
{
    class Subject;

    class C_Score : public Component
    {
    public:
        C_Score(GameObject* pGameObject);
       virtual ~C_Score() noexcept;

       C_Score(const C_Score& other) = delete;
       C_Score(C_Score&& other) noexcept = delete;
       C_Score& operator=(const C_Score& other) = delete;
       C_Score& operator=(C_Score&& other) noexcept = delete;

        int GetScore() const;
        void IncreaseScore(int amount);
        Subject* GetSubject() const;

    private:
        int m_Score;
        Subject* m_pSubject;
    };
}
