#pragma once
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:
		Component(GameObject* pGameObject);

		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		virtual ~Component() noexcept;
		virtual void Update();
		virtual void FixedUpdate();
		virtual void LateUpdate();
		virtual void Render() const;

	protected:
		GameObject* m_pGameObject;
	};
}

