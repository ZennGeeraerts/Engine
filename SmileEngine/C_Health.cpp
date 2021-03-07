#include "MiniginPCH.h"
#include "C_Health.h"
#include "Observer.h"
#include "Subject.h"
#include "C_Lives.h"

dae::C_Health::C_Health(GameObject* pGameObject)
	: Component(pGameObject)
	, m_MaxHealth{ 1 }
	, m_CurrentHealth{ 1 }
	, m_IsDead{ false }
	, m_IsInitialized{ false }
	, m_pSubject{ new Subject{} }
	, m_pLives{ nullptr }
{
	m_pLives = pGameObject->GetComponent<C_Lives>();
	if (!m_pLives)
	{
		std::cerr << "LivesComponent not found on HealthComponent" << std::endl;
	}
}

void dae::C_Health::Update()
{
	if (!m_IsInitialized)
	{
		m_pSubject->Notify(m_pGameObject, "HealthCreated");
		m_pSubject->Notify(m_pGameObject, "LivesUpdated");
		m_IsInitialized = true;
	}
}

void dae::C_Health::SetHealth(int health)
{
	m_MaxHealth = health;
	m_CurrentHealth = health;
}

dae::C_Health::~C_Health()
{
	delete m_pSubject;
}

void dae::C_Health::TakeDamage(int damage)
{
	m_CurrentHealth -= damage;

	if (m_CurrentHealth <= 0)
	{
		m_pLives->RemoveLive();
		m_pSubject->Notify(m_pGameObject, "PlayerDied");

		if (m_pLives->GetLives() > 0)
		{
			m_CurrentHealth = m_MaxHealth;
		}
	}
}

void dae::C_Health::Kill()
{
	TakeDamage(m_CurrentHealth);
}

int dae::C_Health::GetHealth() const
{
	return m_CurrentHealth;
}

dae::Subject* dae::C_Health::GetSubject() const
{
	return m_pSubject;
}
