#include "MiniginPCH.h"
#include "Prefab.h"
#include "GameObject.h"

int dae::Prefab::m_InstanceCount{ 0 };

dae::Prefab::Prefab(const std::string& name)
	: m_pGameObject{ new GameObject{ name + std::to_string(m_InstanceCount) } }
{
	++m_InstanceCount;
}
