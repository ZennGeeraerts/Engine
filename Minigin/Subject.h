#pragma once
#include <string>

namespace dae
{
	class Observer;
	class GameObject;

	class Subject final
	{
	public:
		Subject();
		~Subject() = default;
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void Notify(GameObject* pGameObject, const std::string& eventName);

	private:
		Observer* m_pHead;
	};
}

