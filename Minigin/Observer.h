#pragma once

namespace dae
{
	class GameObject;
	class Subject;

	class Observer
	{
		friend class Subject;
	public:
		Observer(Subject* pSubject);
		virtual ~Observer();
		virtual void Notify(GameObject* pGameObject, const std::string& eventName) = 0;

	private:
		Observer* m_pNext;
		Subject* const m_pSubject;
	};

	class OnDead final : public Observer
	{
	public:
		OnDead(Subject* pSubject);
		void Notify(GameObject* pGameObject, const std::string& eventName) override;
	};
}

