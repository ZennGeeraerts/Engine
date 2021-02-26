#include "MiniginPCH.h"
#include "Observer.h"
#include "GameObject.h"
#include "Subject.h"

#include "C_Transform.h"

dae::Observer::Observer(Subject* pSubject)
	: m_pSubject{ pSubject }
	, m_pNext{ nullptr }
{

}

dae::Observer::~Observer()
{
	if (m_pSubject)
	{
		m_pSubject->RemoveObserver(this);
	}
}


// OnDead
dae::OnDead::OnDead(Subject* pSubject)
	: Observer(pSubject)
{

}

void dae::OnDead::Notify(GameObject* pGameObject, const std::string& eventName)
{
	std::cout << eventName << ": " << pGameObject->GetName() << " PlayerDied" << std::endl;
}
