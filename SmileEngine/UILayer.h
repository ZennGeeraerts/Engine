#pragma once

struct SDL_Window;

namespace dae
{
	class Subject;

	class UILayer
	{
	public:
		UILayer(const glm::vec2& pos, const std::string& name, SDL_Window* pWindow);
		virtual ~UILayer();

		virtual void Render() = 0;
		std::string GetName() const;

	protected:
		SDL_Window* m_pWindow;
		glm::vec2 m_Position;

	private:
		std::string m_Name;
	};
}

