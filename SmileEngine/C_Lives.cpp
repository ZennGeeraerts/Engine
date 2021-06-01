#include "SmileEnginePCH.h"
#include "C_Lives.h"
#include "Subject.h"

dae::C_Lives::C_Lives(GameObject* pGameObject)
	: Component(pGameObject)
	, m_Lives{ 1 }
	, m_pSubject{ new Subject{} }
{
}

void dae::C_Lives::SetLives(int lives)
{
	m_Lives = lives;
}

int dae::C_Lives::GetLives() const
{
	return m_Lives;
}

void dae::C_Lives::RemoveLive()
{
	if (m_Lives > 0)
	{
		--m_Lives;
	}

	if (m_Lives == 0)
	{
		m_pSubject->Notify(m_pGameObject, "GameOver");
	}
}

dae::Subject* dae::C_Lives::GetSubject() const
{
	return m_pSubject;
}
