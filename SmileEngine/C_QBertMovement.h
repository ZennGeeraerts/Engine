#pragma once
#include "Component.h"

namespace dae
{
    class C_Transform;

    class C_QBertMovement : public Component
    {
    public:
        C_QBertMovement(GameObject* pGameObject);
        virtual ~C_QBertMovement() noexcept = default;

        void SetTileMap(GameObject* pTileMap);

        void MoveBottomLeft();
        void MoveTopRight();
        void MoveBottomRight();
        void MoveTopLeft();

        int GetTileSize() const;

    private:
        int CalculateCurrentRow();
        void MoveToTile();
        void PlayJumpSound() const;

        int m_CurrentTileIndex;
        C_Transform* m_pTransform;
        GameObject* m_pTileMap;
        int m_TileSize;
    };
}

