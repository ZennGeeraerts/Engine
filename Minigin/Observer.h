#pragma once

namespace dae
{
	class GameObject;
	class Subject;

	class Observer
	{
		friend class Subject;
	public:
		Observer(const std::vector<Subject*> pSubjects);
		virtual ~Observer();
		virtual void Notify(GameObject* pGameObject, const std::string& eventName) = 0;

	private:
		Observer* m_pNext;
		const std::vector<Subject*> m_pSubjects;
	};
}

