#include "SmileEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	if (!m_CurrentScene.get())
	{
		return;
	}
	else if (m_CurrentScene->GetIsMarkedForDelete())
	{
		RemoveScene(m_CurrentScene);
		m_CurrentScene = nullptr;
		return;
	}
	else if (m_CurrentScene->GetIsMarkedforRestart())
	{
		m_CurrentScene->Restart();
	}

	m_CurrentScene->Update();
}

void dae::SceneManager::FixedUpdate()
{
	if (!m_CurrentScene.get())
	{
		return;
	}

	m_CurrentScene->FixedUpdate();
}

void dae::SceneManager::LateUpdate()
{
	if (!m_CurrentScene.get())
	{
		return;
	}

	m_CurrentScene->LateUpdate();
}

#pragma warning (push)
#pragma warning (disable:26816)
dae::Scene& dae::SceneManager::AddScene(std::shared_ptr<Scene> pScene)
{
	m_Scenes.push_back(pScene);
	m_CurrentScene = pScene;
	return *pScene;
}
#pragma warning(pop)

void dae::SceneManager::RemoveScene(int index)
{
	if ((index >= 0) && (index < static_cast<int>(m_Scenes.size())))
	{
		m_Scenes.erase(m_Scenes.begin() + index);
	}
	else
	{
		std::cout << "SceneManager::RemoveScene(int index) > index out of range" << std::endl;
	}
}

void dae::SceneManager::RemoveScene(std::shared_ptr<Scene> pScene)
{
	m_Scenes.erase(std::find(m_Scenes.begin(), m_Scenes.end(), pScene));
}

void dae::SceneManager::SetScene(int index)
{
	if ((index >= 0) && (index < static_cast<int>(m_Scenes.size())))
	{
		m_CurrentScene = m_Scenes[index];
	}
	else
	{
		std::cout << "SceneManager::SetScene(int index) > index out of range" << std::endl;
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(int index) const
{
	if ((index < static_cast<int>(m_Scenes.size())) && (index > -1))
	{
		return m_Scenes[index];
	}

	std::cout << "SceneManager::GetScene(int index) > index out of range, returned nullptr" << std::endl;
	return nullptr;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetCurrentScene() const
{
	return m_CurrentScene;
}
