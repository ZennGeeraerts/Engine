#pragma once
#include "Component.h"

namespace dae
{
	class C_QBertMovement;

	class C_UggController final : public Component
	{
	public:
		C_UggController(GameObject* pGameObject);

		void Update() override;

	private:
		C_QBertMovement* m_pMovement;
	};
}
