#pragma once
#include "Component.h"

namespace dae
{
	class C_QBertMovement;

	class C_SlickAndSlamController : public Component
	{
	public:
		C_SlickAndSlamController(GameObject* pGameObject);

		void Update() override;

	private:
		C_QBertMovement* m_pMovement;
	};
}

