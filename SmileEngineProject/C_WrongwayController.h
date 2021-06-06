#pragma once
#include "Component.h"

namespace dae
{
	class C_QBertMovement;

	class C_WrongwayController : public Component
	{
	public:
		C_WrongwayController(GameObject* pGameObject);

		void Update() override;

	private:
		C_QBertMovement* m_pMovement;
	};
}

