#pragma once
#include "Observer.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Window;

namespace dae
{
	class Subject;

	class UILayer : public Observer
	{
	public:
		UILayer(const glm::vec2& pos, const std::string& name, SDL_Window* pWindow, const std::vector<Subject*> pSubjects);
		virtual ~UILayer();

		virtual void Render() = 0;
		virtual void Notify(GameObject* pGameObject, const std::string& eventName) = 0;
		std::string GetName() const;

	protected:
		SDL_Window* m_pWindow;
		glm::vec2 m_Position;

	private:
		std::string m_Name;
	};
}

