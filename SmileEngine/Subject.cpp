#include "SmileEnginePCH.h"
#include "Subject.h"
#include "Observer.h"

dae::Subject::Subject()
	: m_pHead{ nullptr }
{

}

void dae::Subject::AddObserver(Observer* pObserver)
{
	pObserver->m_pNext = m_pHead;
	m_pHead = pObserver;
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	if (m_pHead == pObserver)
	{
		m_pHead = pObserver->m_pNext;
		pObserver->m_pNext = nullptr;
		return;
	}

	auto pCurrent{ m_pHead };
	while (pCurrent)
	{
		if (pCurrent->m_pNext == pObserver)
		{
			pCurrent->m_pNext = pObserver->m_pNext;
			pObserver->m_pNext = nullptr;
			return;
		}

		pCurrent = pCurrent->m_pNext;
	}
}

void dae::Subject::Notify(GameObject* pGameObject, const std::string& eventName)
{
	auto pCurrent{ m_pHead };
	while (pCurrent)
	{
		pCurrent->Notify(pGameObject, eventName);
		pCurrent = pCurrent->m_pNext;
	}
}
