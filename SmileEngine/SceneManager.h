#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		dae::Scene& AddScene(std::shared_ptr<Scene> pScene);
		void RemoveScene(int index);
		void RemoveScene(std::shared_ptr<Scene> pScene);
		void SetScene(int index);

		void Update();
		void FixedUpdate();
		void LateUpdate();

		std::shared_ptr<Scene> GetScene(int index) const;
		std::shared_ptr<Scene> GetCurrentScene() const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_CurrentScene;
	};
}
