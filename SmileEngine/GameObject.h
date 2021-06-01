#pragma once

namespace dae
{
	class Component;
	class C_Transform;
	class Scene;

	class GameObject final
	{
	public:
		GameObject();
		explicit GameObject(const std::string& name);
		virtual ~GameObject();
		GameObject(const GameObject & other) = delete;
		GameObject(GameObject && other) = delete;
		GameObject& operator=(const GameObject & other) = delete;
		GameObject& operator=(GameObject && other) = delete;

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		template <typename ComponentType>
		ComponentType* GetComponent() const
		{
			ComponentType* pComponent{ nullptr };

			for (Component* pElement : m_pComponents)
			{
				pComponent = dynamic_cast<ComponentType*>(pElement);

				if (pComponent)
				{
					return pComponent;
				}
			}

			return nullptr;
		}

		template <typename ComponentType>
		ComponentType* AddComponent()
		{
			// Check at compile time if ComponentType is a component
			static_assert(std::is_base_of<Component, ComponentType>::value, "Invalid component.");

			// Return component if it already existed
			ComponentType* pExistingComponent{ GetComponent<ComponentType>() };
			if (pExistingComponent)
			{
				return pExistingComponent;
			}

			ComponentType* pNewComponent{ new ComponentType{ this } };
			m_pComponents.push_back(pNewComponent);
			return pNewComponent;
		}

		void SetName(const std::string& name);
		void SetScene(Scene* pScene);
		void AddChild(GameObject* pChild);
		GameObject* GetChildByName(const std::string& name) const;
		GameObject* GetChildByIndex(int index) const;
		const std::vector<GameObject*>& GetChildren() const;
		//std::ostream& operator<<(std::ostream& os, const GameObject& dt);

		C_Transform* GetTransform() const;
		const std::string& GetName() const;
		Scene* GetScene() const;

		static int GetInstanceCount();

	protected:
		Scene* m_pScene;

	private:
		std::vector<Component*> m_pComponents;
		std::vector<GameObject*> m_pChildren;
		std::string m_Name;
		C_Transform* m_pTransform;
		bool m_IsDead;

		static int m_InstanceCount;
	};
}
