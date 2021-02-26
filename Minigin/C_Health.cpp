#include "MiniginPCH.h"
#include "C_Health.h"
#include "Observer.h"

dae::C_Health::C_Health(GameObject* pGameObject)
	: Component(pGameObject)
	, m_MaxHealth{ 1 }
	, m_CurrentHealth{ 1 }
	, m_Subject{}
	, m_pOnDead{ new OnDead{ &m_Subject } }
{
	m_Subject.AddObserver(m_pOnDead);
}

void dae::C_Health::SetHealth(int health)
{
	m_MaxHealth = health;
	m_CurrentHealth = health;
}

dae::C_Health::~C_Health()
{
	delete m_pOnDead;
}

void dae::C_Health::TakeDamage(int damage)
{
	m_CurrentHealth -= damage;

	if (!m_IsDead && (m_CurrentHealth <= 0))
	{
		m_Subject.Notify(m_pGameObject, "OnDead");
		m_IsDead = true;
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
