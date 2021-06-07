#pragma once
#include <string>
#include <vector>

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
		virtual ~GameObject() noexcept;
		GameObject(const GameObject & other) = delete;
		GameObject(GameObject && other) noexcept = delete;
		GameObject& operator=(const GameObject & other) = delete;
		GameObject& operator=(GameObject && other) noexcept = delete;

		void Update();
		void FixedUpdate();
		void LateUpdate();

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
		void SetTag(const std::string& tag);
		void AddChild(GameObject* pChild);
		void MarkForDelete();
		void SetEnabled(bool isEnabled);

		GameObject* GetChildByName(const std::string& name) const;
		GameObject* GetChildByIndex(int index) const;
		const std::vector<GameObject*>& GetChildren() const;

		C_Transform* GetTransform() const;
		const std::string& GetName() const;
		Scene* GetScene() const;
		bool GetIsMarkedForDelete() const;
		const std::string& GetTag() const;
		bool GetIsEnabled() const;

		static int GetInstanceCount();

	protected:
		Scene* m_pScene;

	private:
		std::vector<Component*> m_pComponents;
		std::vector<GameObject*> m_pChildren;
		std::string m_Name;
		C_Transform* m_pTransform;
		bool m_IsMarkedForDelete;
		std::string m_Tag;
		bool m_IsEnabled;

		static int m_InstanceCount;
	};
}
