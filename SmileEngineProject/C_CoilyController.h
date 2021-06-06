#pragma once
#include "Component.h"

namespace dae
{
	class C_QBertMovement;
	class C_Teleport;

	class C_CoilyController final : public Component
	{
	public:
		C_CoilyController(GameObject* pGameObject);
		
		void SetNrOfRows(int nrOfRows);
		void SetIsInputControlled(bool isInputControlled);

		void Update() override;
		void OnPlayerTeleport(C_Teleport* pTeleport);

	private:
		void MoveToBottom();
		void ChasePlayer();

		C_QBertMovement* m_pMovement;
		bool m_HasReachedBottom;
		int m_NrOfRows;
		C_Teleport* m_pTeleport;
		bool m_IsInputControlled;
	};
}

