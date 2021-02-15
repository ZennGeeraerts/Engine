#pragma once

namespace dae
{
	class Component;
	class Transform;

	class GameObject final
	{
	public:
		GameObject();
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

		Transform* GetTransform() const;

	private:
		std::vector<Component*> m_pComponents;
		Transform* m_pTransform;
		bool m_IsDead;
	};
}
