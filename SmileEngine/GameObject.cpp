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
	, m_IsMarkedForDelete{ false }
	, m_pScene{ nullptr }
	, m_Tag{ "" }
	, m_IsEnabled{ true }
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
	if (!m_IsEnabled)
	{
		return;
	}

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
	if (!m_IsEnabled)
	{
		return;
	}

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
	if (!m_IsEnabled)
	{
		return;
	}

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
	if (!m_IsEnabled)
	{
		return;
	}

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

void dae::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	if (!pChild->GetScene())
	{
		m_pChildren.push_back(pChild);
		pChild->SetScene(m_pScene);
	}
	else
	{
		std::cout << "GameObject::AddChild(GameObject* pChild) > child is already added to a scene" << std::endl;
	}
}

void dae::GameObject::MarkForDelete()
{
	m_IsMarkedForDelete = true;
}

void dae::GameObject::SetEnabled(bool isEnabled)
{
	m_IsEnabled = isEnabled;
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

bool dae::GameObject::GetIsMarkedForDelete() const
{
	return m_IsMarkedForDelete;
}

int dae::GameObject::GetInstanceCount()
{
	return m_InstanceCount;
}

const std::string& dae::GameObject::GetTag() const
{
	return m_Tag;
}

bool dae::GameObject::GetIsEnabled() const
{
	return m_IsEnabled;
}