#pragma once
#include "Prefab.h"
#include "XBoxController.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Window;

namespace dae
{
	class Player final : public Prefab
	{
	public:
		Player(const glm::vec2& uiPos, SDL_Window* pWindow, XBoxController::ControllerButton dieButton, XBoxController::ControllerButton increaseScoreButton);
		std::shared_ptr<GameObject> CreatePrefab() override;

	private:
		SDL_Window* m_pWindow;
		XBoxController::ControllerButton m_DieButton;
		XBoxController::ControllerButton m_IncreaseScoreButton;
		glm::vec2 m_UIPosition;
	};
}

