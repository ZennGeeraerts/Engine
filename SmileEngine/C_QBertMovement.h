#pragma once
#include "Component.h"

namespace dae
{
    class C_Transform;
    class Subject;

    class C_QBertMovement final : public Component
    {
    public:
        enum class TileChange
        {
            eNone,
            eUpdate,
            eRevert
        };

        C_QBertMovement(GameObject* pGameObject);
        virtual ~C_QBertMovement() noexcept = default;

        void SetTileMap(GameObject* pTileMap);
        void SetTexturePaths(const std::vector<std::string>& texturePaths);
        void SetStartTile(int tileIndex);
        void SetTileChange(TileChange tileChange);

        void Update() override;

        void MoveToStartTile(bool teleport);
        void SetTile(int tileIndex, bool teleport);
        void MoveBottomLeft();
        void MoveTopRight();
        void MoveBottomRight();
        void MoveTopLeft();
        void MoveLeft();
        void MoveRight();

        int CalculateCurrentRow() const;

        int GetTileSize() const;
        Subject* GetSubject() const;
        int GetCurrentTileIndex() const;

    private:
        void MoveToTile();
        void PlayJumpSound() const;
        void CheckValidTile(int previousRow);

        int m_CurrentTileIndex;
        C_Transform* m_pTransform;
        GameObject* m_pTileMap;
        int m_TileSize;
        const float m_MoveSpeed{ 50.f };
        bool m_HasDestPosReached;
        std::vector<std::string> m_TexturePaths;

        Subject* m_pSubject;
        int m_StartTile;
        TileChange m_TileChange;
    };
}

