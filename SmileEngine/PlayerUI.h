#pragma once
#include "UILayer.h"
#include "Observer.h"

namespace dae
{
	class PlayerUI final : public UILayer, public Observer
	{
	public:
		PlayerUI(const glm::vec2& pos, const std::vector<Subject*>& pSubjects);
		void Render() override;
		void Notify(GameObject* pGameObject, const std::string& eventName) override;

	private:
		std::string m_PlayerName;
		std::string m_NotifyText;
		int m_RemainingLives;
		int m_Score;
	};
}

