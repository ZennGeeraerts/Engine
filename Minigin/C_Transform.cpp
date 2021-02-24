#include "MiniginPCH.h"
#include "C_Transform.h"

dae::C_Transform::C_Transform(GameObject* pGameObject)
	: Component(pGameObject)
{

}

void dae::C_Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
