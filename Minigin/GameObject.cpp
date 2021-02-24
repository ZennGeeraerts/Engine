#include "MiniginPCH.h"
#include "GameObject.h"
#include "C_Transform.h"

dae::GameObject::GameObject()
	: m_pComponents{}
	, m_pTransform{ nullptr }
	, m_IsDead{ false }
{
	m_pTransform = AddComponent<C_Transform>();
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