#include "SmileEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <memory>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_pGameObjects.push_back(object);
}

void Scene::Update()
{
	for(auto& pObject : m_pGameObjects)
	{
		pObject->Update();
	}
}

void Scene::FixedUpdate()
{
	for (auto& pObject : m_pGameObjects)
	{
		pObject->FixedUpdate();
	}
}

void Scene::LateUpdate()
{
	for (auto& pObject : m_pGameObjects)
	{
		pObject->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& pObject : m_pGameObjects)
	{
		pObject->Render();
	}
}

GameObject* Scene::GetGameObjectByName(const std::string& name) const
{
	auto it = std::find_if(m_pGameObjects.begin(), m_pGameObjects.end(),
		[name] (std::shared_ptr<dae::GameObject> pGameObject)
		{
			return pGameObject->GetName() == name;
		});

	if (it != m_pGameObjects.end())
	{
		return (*it).get();
	}

	std::cout << "Scene::GetGameObjectByName(const std::string& name) > name not found, returned nullptr" << std::endl;
	return nullptr;
}
