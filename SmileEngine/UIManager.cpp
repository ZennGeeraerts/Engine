#include "SmileEnginePCH.h"
#include "UIManager.h"
#include "UILayer.h"

dae::UIManager::~UIManager()
{
	for (auto pUILayer : m_pUILayers)
	{
		delete pUILayer;
	}
}

void dae::UIManager::Render()
{
	for (auto pUILayer : m_pUILayers)
	{
		pUILayer->Render();
	}
}

void dae::UIManager::AddUILayer(UILayer* pUILayer)
{
	m_pUILayers.push_back(pUILayer);
}

void dae::UIManager::RemoveUILayer(UILayer* pUILayer)
{
	RemoveUILayer(pUILayer->GetName());
}

void dae::UIManager::RemoveUILayer(const std::string& name)
{
	auto it = std::find_if(m_pUILayers.begin(), m_pUILayers.end(),
		[name] (UILayer* pUILayer)
		{
			return pUILayer->GetName() == name;
		}
	);

	if (it != m_pUILayers.end())
	{
		m_pUILayers.erase(it);
	}
}
