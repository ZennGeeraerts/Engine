#include "SmileEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <memory>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const GameSettings& gameSettings)
	: Scene(gameSettings, "")
{

}

Scene::Scene(const GameSettings& gameSettings, const std::string& name) 
	: m_Name(name)
	, m_IsMarkedForDelete{ false }
	, m_IsMarkedForRestart{ false }
	, m_GameSettings{ gameSettings }
{
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& pObject)
{
	if (!pObject->GetScene())
	{ 
		m_pGameObjects.push_back(pObject);
		pObject->SetScene(this);
	}
	else
	{
		std::cout << "Scene::Add(const std::shared_ptr<GameObject>& pObject) > GameObject is already attached to a scene" << std::endl;
	}
}

void Scene::Update()
{
	std::vector<std::shared_ptr<GameObject>> pToBeDeleted{};

	for (auto& pObject : m_pGameObjects)
	{
		pObject->Update();

		if (pObject->GetIsMarkedForDelete())
		{
			pToBeDeleted.push_back(pObject);
		}
	}

	// Delete game objects
	for (auto& pObject : pToBeDeleted)
	{
		m_pGameObjects.erase(std::remove(m_pGameObjects.begin(), m_pGameObjects.end(), pObject));
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

void Scene::GetGameObjectsWithTag(std::vector<GameObject*>& pGameObjects, const std::string& tag)
{
	pGameObjects.clear();

	auto it = m_pGameObjects.begin();
	while (true)
	{
		it = std::find_if(it, m_pGameObjects.end(),
			[tag](std::shared_ptr<dae::GameObject> pGameObject)
			{
				return pGameObject->GetTag() == tag;
			});

		if (it != m_pGameObjects.end())
		{
			pGameObjects.push_back((*it).get());
			++it;
		}
		else
		{
			break;
		}
	}
}

void Scene::MarkForDelete()
{
	m_IsMarkedForDelete = true;
}

void Scene::MarkForRestart()
{
	m_IsMarkedForRestart = true;
}

void Scene::Restart()
{
	m_pGameObjects.clear();
	CreateScene();
	m_IsMarkedForRestart = false;
}

bool Scene::GetIsMarkedForDelete() const
{
	return m_IsMarkedForDelete;
}

bool Scene::GetIsMarkedforRestart() const
{
	return m_IsMarkedForRestart;
}

void Scene::OnSceneEnd()
{}
