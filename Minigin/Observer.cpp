#include "MiniginPCH.h"
#include "Observer.h"
#include "GameObject.h"
#include "Subject.h"

#include "C_Transform.h"
#include "C_Lives.h"

dae::Observer::Observer(const std::vector<Subject*> pSubjects)
	: m_pSubjects{ pSubjects }
	, m_pNext{ nullptr }
{

}

dae::Observer::~Observer()
{
	for (auto pSubject : m_pSubjects)
	{
		if (pSubject)
		{
			pSubject->RemoveObserver(this);
		}
	}
}
