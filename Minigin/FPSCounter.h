#pragma once
#include "Component.h"
#include "Text.h"

namespace dae
{
	class FPSCounter final : public Component
	{
	public:
		FPSCounter(GameObject* pGameObject);
		void Update() override;
		void SetUpdateRate(float updateRate);
	private:
		Text* m_pText;
		float m_UpdateRate;
		float m_ElapsedSec;
	};
}

