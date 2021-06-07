#pragma once

namespace dae
{
	class GameObject;
	class Subject;

	class Observer
	{
		friend class Subject;
	public:
		Observer();
		Observer(const std::vector<Subject*> pSubjects);
		virtual ~Observer() noexcept;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		void AddSubject(Subject* pSubject);
		virtual void Notify(GameObject* pGameObject, const std::string& eventName) = 0;

	private:
		Observer* m_pNext;
		std::vector<Subject*> m_pSubjects;
	};
}

