#pragma once
#include "UILayer.h"
namespace dae
{
	class GameModeMenu final : public UILayer
	{
	public:
		GameModeMenu(const glm::vec2& pos, SDL_Window* pWindow);
		void Notify(GameObject* pGameObject, const std::string& eventName) override;
		void Render() override;
	};
}
