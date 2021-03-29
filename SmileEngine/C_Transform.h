#pragma once
#include "Component.h"

namespace dae
{
	class C_Transform final : public Component
	{
	public:
		C_Transform(GameObject* pGameObject);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
