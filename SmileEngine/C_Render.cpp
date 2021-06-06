#include "SmileEnginePCH.h"
#include "C_Render.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "C_Transform.h"
dae::C_Render::C_Render(GameObject* pGameObject)
	: Component(pGameObject)
{
	dae::Renderer::GetInstance().RegisterRenderComponent(this);
}

dae::C_Render::~C_Render()
{
	dae::Renderer::GetInstance().UnRegisterRenderComponent(this);
}

void dae::C_Render::Render() const
{
	if (m_pTexture)
	{
		const auto pos = m_pGameObject->GetComponent<C_Transform>()->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::C_Render::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::C_Render::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
}

std::shared_ptr<dae::Texture2D> dae::C_Render::GetTexture() const
{
	return m_pTexture;
}
