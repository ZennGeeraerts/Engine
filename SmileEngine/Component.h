#pragma once
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:
		Component(GameObject* pGameObject);
		virtual ~Component();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void LateUpdate();
		virtual void Render() const;

	protected:
		GameObject* m_pGameObject;
	};
}

