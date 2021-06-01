#pragma once
#include "Prefab.h"

struct SDL_Window;

namespace dae
{
	class Player final : public Prefab
	{
	public:
		Player(const glm::vec2& uiPos, SDL_Window* pWindow);
		std::shared_ptr<GameObject> CreatePrefab() override;

	private:
		SDL_Window* m_pWindow;
		glm::vec2 m_UIPosition;
	};
}

