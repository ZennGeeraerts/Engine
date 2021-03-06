#pragma once
#include "SceneManager.h"
#include "SmileEngine.h"

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		Scene(const GameSettings& gameSettings);
		Scene(const GameSettings& gameSettings, const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Add(const std::shared_ptr<GameObject>& pObject);

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void MarkForDelete();
		void MarkForRestart();
		void Restart();
		bool GetIsMarkedForDelete() const;
		bool GetIsMarkedforRestart() const;
		virtual void CreateScene() = 0;
		virtual void OnSceneEnd();

		GameObject* GetGameObjectByName(const std::string& name) const;
		void GetGameObjectsWithTag(std::vector<GameObject*>& pGameObjects, const std::string& tag);

	protected:
		GameSettings m_GameSettings;

	private:
		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_pGameObjects{};

		static unsigned int m_IdCounter;
		bool m_IsMarkedForDelete;
		bool m_IsMarkedForRestart;
	};

}
