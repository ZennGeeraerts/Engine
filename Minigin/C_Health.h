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
		~C_Health();
		C_Health(const C_Health&) = delete;
		C_Health(C_Health&&) = delete;

		void Update() override;

		void SetHealth(int health);

		void TakeDamage(int damage);
		void Kill();

		int GetHealth() const;
		Subject* GetSubject() const;

		C_Health& operator=(const C_Health&) = delete;
		C_Health& operator=(C_Health&&) = delete;

	private:
		int m_MaxHealth;
		int m_CurrentHealth;
		bool m_IsDead;
		bool m_IsInitialized;

		Subject* m_pSubject;
		C_Lives* m_pLives;
	};
}

