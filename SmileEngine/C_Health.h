#pragma once
#include "Component.h"
#include "C_Lives.h"

namespace dae
{
	class Observer;

	class C_Health final : public Component
	{
	public:
		C_Health(GameObject* pGameObject);
		virtual ~C_Health() noexcept;
		C_Health(const C_Health&) = delete;
		C_Health(C_Health&&) noexcept = delete;

		void Update() override;

		void SetHealth(int health);

		void TakeDamage(int damage);
		void Kill();

		int GetHealth() const;
		Subject* GetUISubject() const;
		Subject* GetGameManagerSubject() const;

		C_Health& operator=(const C_Health&) = delete;
		C_Health& operator=(C_Health&&) noexcept = delete;

	private:
		int m_MaxHealth;
		int m_CurrentHealth;
		bool m_IsDead;
		bool m_IsInitialized;

		Subject* m_pUISubject;
		Subject* m_pGameManagerSubject;
		C_Lives* m_pLives;
	};
}

