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
		~Subject() noexcept;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) noexcept = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) noexcept = delete;

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void Notify(GameObject* pGameObject, const std::string& eventName);

	private:
		Observer* m_pHead;
	};
}

