#pragma once
#include "Component.h"
#include "C_QBertMovement.h"

namespace dae
{
	class C_Render;

	class C_Teleport final : public Component
	{
	public:
		C_Teleport(GameObject* pGameObject);
		
		void SetConnectedTile(int connectedTile, C_QBertMovement::MovementDirection movementDir);
		void SetTexturePaths(const std::vector<std::string>& texturePaths);

		void Update() override;
		void Teleport(GameObject* pPlayer);

		int GetConnectedTile() const;
		C_QBertMovement::MovementDirection GetMovementDirection() const;

	private:
		int m_ConnectedTile;
		C_QBertMovement::MovementDirection m_MovementDirection;
		C_Render* m_pRenderComponent;
		std::vector<std::string> m_TexturePaths;
		int m_TextureIndex;

		float m_RotationTime;
		const float m_MaxRotationTime{ 0.1f };
		
		GameObject* m_pPlayer;
		glm::vec3 m_StartPosition;
		glm::vec3 m_DestPosition;
		const float m_MoveSpeed{ 50.f };
	};
}

