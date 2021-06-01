#include "SmileEnginePCH.h"
#include "GameObject.h"
#include "C_Transform.h"

int dae::GameObject::m_InstanceCount{ 0 };

dae::GameObject::GameObject()
	: GameObject("GameObject" + m_InstanceCount)
{
	
}

dae::GameObject::GameObject(const std::string& name)
	: m_pComponents{}
	, m_pChildren{}
	, m_Name{ name }
	, m_pTransform{ nullptr }
	, m_IsDead{ false }
	, m_pScene{ nullptr }
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

	for (GameObject* pChild : m_pChildren)
	{
		delete pChild;
	}
}

void dae::GameObject::Update()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->Update();
	}

	for (GameObject* pChild : m_pChildren)
	{
		pChild->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}

	for (GameObject* pChild : m_pChildren)
	{
		pChild->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->LateUpdate();
	}

	for (GameObject* pChild : m_pChildren)
	{
		pChild->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->Render();
	}

	for (GameObject* pChild : m_pChildren)
	{
		pChild->Render();
	}
}

void dae::GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

void dae::GameObject::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
}

dae::GameObject* dae::GameObject::GetChildByName(const std::string& name) const
{
	auto it = std::find_if(m_pChildren.begin(), m_pChildren.end(),
		[name](GameObject* pChild)
		{
			return pChild->GetName() == name;
		});

	if (it != m_pChildren.end())
	{
		return (*it);
	}

	std::cout << "GameObject::GetChildByName(const std::string& name) > name not found, returned nullptr" << std::endl;
	return nullptr;
}

dae::GameObject* dae::GameObject::GetChildByIndex(int index) const
{
	if ((index < m_pChildren.size()) && (index > -1))
	{
		return m_pChildren[index];
	}

	std::cout << "GameObject::GetChildByIndex(int index) > index out of range, returned nullptr" << std::endl;
	return nullptr;
}

const std::vector<dae::GameObject*>& dae::GameObject::GetChildren() const
{
	return m_pChildren;
}

dae::C_Transform* dae::GameObject::GetTransform() const
{
	return m_pTransform;
}

const std::string& dae::GameObject::GetName() const
{
	return m_Name;
}

dae::Scene* dae::GameObject::GetScene() const
{
	return m_pScene;
}

int dae::GameObject::GetInstanceCount()
{
	return m_InstanceCount;
}