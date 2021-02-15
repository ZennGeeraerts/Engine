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
	private:
		Text* m_pText;
	};
}

