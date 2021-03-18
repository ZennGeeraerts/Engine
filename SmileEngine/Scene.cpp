#include "SmileEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"

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

