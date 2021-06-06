#pragma once
#include "Component.h"
#include "Observer.h"
#include <unordered_map>

namespace dae
{
	class SmileEngine;

	class C_GameManager final : public Component, public Observer
	{
	public:
		C_GameManager(GameObject* pGameObject);

		void SetRevertTileOnMaxStage(bool revertTileOnMaxStage);

		void Update() override;
		void Notify(GameObject* pGameObject, const std::string& eventName) override;
		void SpawnOverTime(GameObject* pGameObject, float timeToSpawn);

	private:
		void CheckWinCondition();
		void SpawnGameObjects();
		void CheckRestart();

		bool m_IsWinCondition;
		std::unordered_map<GameObject*, float> m_ToBeSpawned;
		bool m_RevertTileOnMaxStage;
	};
}

