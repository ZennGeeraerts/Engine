#include "SmileEnginePCH.h"
#include "C_Score.h"
#include "GameObject.h"
#include "Subject.h"

dae::C_Score::C_Score(GameObject* pGameObject)
	: Component(pGameObject)
	, m_Score{ 0 }
	, m_pSubject{ new Subject{} }
{

}

int dae::C_Score::GetScore() const
{
	return m_Score;
}

void dae::C_Score::IncreaseScore(int amount)
{
	m_Score += amount;
	m_pSubject->Notify(m_pGameObject, "ScoreIncrease");
}

dae::Subject* dae::C_Score::GetSubject() const
{
	return m_pSubject;
}
