#include "SmileEnginePCH.h"
#include "GameObject.h"
#include "C_Transform.h"
#include "Subject.h"

int dae::GameObject::m_InstanceCount{ 0 };

dae::GameObject::GameObject()
	: GameObject("GameObject" + m_InstanceCount)
{
	
}

dae::GameObject::GameObject(const std::string& name)
	: m_pComponents{}
	, m_Name{ name }
	, m_pTransform{ nullptr }
	, m_IsDead{ false }
{
	m_pTransform = AddComponent<C_Transform>();

	++m_InstanceCount;
}

dae::GameObject::~GameObject()
{
	for (Component* pComponent : m_pComponents)
	{
		delete pComponent;
	}
}

void dae::GameObject::Update()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

dae::C_Transform* dae::GameObject::GetTransform() const
{
	return m_pTransform;
}

const std::string& dae::GameObject::GetName() const
{
	return m_Name;
}

int dae::GameObject::GetInstanceCount()
{
	return m_InstanceCount;
}