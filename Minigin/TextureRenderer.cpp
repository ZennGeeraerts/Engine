#include "MiniginPCH.h"
#include "TextureRenderer.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

dae::TextureRenderer::TextureRenderer(GameObject* pGameObject)
	: Component(pGameObject)
{

}

void dae::TextureRenderer::Render() const
{
	if (m_pTexture)
	{
		const auto pos = m_pGameObject->GetComponent<Transform>()->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextureRenderer::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureRenderer::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
}
