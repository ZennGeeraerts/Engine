#pragma once
namespace dae
{
	class GameObject;

	class Prefab
	{
	public:
		Prefab(const std::string& name);
		virtual std::shared_ptr<GameObject> CreatePrefab() = 0;

	protected:
		std::shared_ptr<GameObject> m_pGameObject;

	private:
		static int m_InstanceCount;
	};
}

