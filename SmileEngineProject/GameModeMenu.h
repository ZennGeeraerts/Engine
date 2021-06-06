#pragma once
#include "UILayer.h"
namespace dae
{
	class GameModeMenu final : public UILayer
	{
	public:
		GameModeMenu(const glm::vec2& pos);
		void Render() override;
	};
}
