#pragma once
#include "Component.h"

namespace dae
{
    class C_Transform;
    class Subject;
    class C_Teleport;

    class C_QBertMovement final : public Component
    {
    public:
        enum class TileChange
        {
            eNone,
            eUpdate,
            eRevert
        };

        enum class MovementDirection
        {
            eBottomLeft,
            eTopRight,
            eBottomRight,
            eTopLeft
        };

        C_QBertMovement(GameObject* pGameObject);
        virtual ~C_QBertMovement() noexcept;

        C_QBertMovement(const C_QBertMovement& other) = delete;
        C_QBertMovement(C_QBertMovement&& other) noexcept = delete;
        C_QBertMovement& operator=(const C_QBertMovement& other) = delete;
        C_QBertMovement& operator=(C_QBertMovement&& other) noexcept = delete;

        void SetTileMap(GameObject* pTileMap);
        void SetTexturePaths(const std::vector<std::string>& texturePaths);
        void SetStartTile(int tileIndex);
        void SetTileChange(TileChange tileChange);
        void SetTeleports(const std::vector<C_Teleport*> pTeleports);

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
        bool GetHasDestPosReached() const;

    private:
        void MoveToTile();
        void PlayJumpSound() const;
        void CheckValidTile(int previousRow);
        void Move(int currentRow);
        bool CheckTeleport(MovementDirection movementDir);

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
        std::vector<C_Teleport*> m_pTeleports;
    };
}

