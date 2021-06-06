#pragma once
#include "Component.h"

namespace dae
{
	class C_QBertMovement;

	class C_PlayerCollision : public Component
	{
	public:
		C_PlayerCollision(GameObject* pGameObject);

		void Update() override;

	private:
		std::vector<GameObject*> m_pEnemies;
		std::vector<GameObject*> m_pCatchables;
		bool m_IsAIChanged;
	};
}

