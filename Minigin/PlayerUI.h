#pragma once
#include "UILayer.h"

namespace dae
{
	class PlayerUI final : public UILayer
	{
	public:
		PlayerUI(const glm::vec2& pos, SDL_Window* pWindow, const std::vector<Subject*>& pSubjects);
		void Render() override;
		void Notify(GameObject* pGameObject, const std::string& eventName) override;

	private:
		std::string m_PlayerName;
		std::string m_NotifyText;
		int m_RemainingLives;
		int m_Score;
	};
}

