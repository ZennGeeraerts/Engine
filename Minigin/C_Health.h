#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class Observer;

	class C_Health final : public Component
	{
	public:
		C_Health(GameObject* pGameObject);
		~C_Health();

		void SetHealth(int health);

		void TakeDamage(int damage);
		void Kill();

		int GetHealth() const;

	private:
		int m_MaxHealth;
		int m_CurrentHealth;
		bool m_IsDead;

		Subject m_Subject;
		Observer* m_pOnDead;
	};
}

