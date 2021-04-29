#pragma once
#include "Component.h"
#include "C_Text.h"

namespace dae
{
	class C_FPSCounter final : public Component
	{
	public:
		C_FPSCounter(GameObject* pGameObject);
		C_FPSCounter(const C_FPSCounter& other) = delete;
		C_FPSCounter(C_FPSCounter&& other) noexcept = delete;
		C_FPSCounter& operator=(const C_FPSCounter& other) = delete;
		C_FPSCounter& operator=(C_FPSCounter&& other) noexcept = delete;
		virtual ~C_FPSCounter() noexcept = default;

		void Update() override;
		void SetUpdateRate(float updateRate);
	private:
		C_Text* m_pText;
		float m_UpdateRate;
		float m_ElapsedSec;
	};
}

