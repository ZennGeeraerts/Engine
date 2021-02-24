#include "MiniginPCH.h"
#include "C_Renderer.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "C_Transform.h"

dae::C_Renderer::C_Renderer(GameObject* pGameObject)
	: Component(pGameObject)
{

}

void dae::C_Renderer::Render() const
{
	if (m_pTexture)
	{
		const auto pos = m_pGameObject->GetComponent<C_Transform>()->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::C_Renderer::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::C_Renderer::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
}
