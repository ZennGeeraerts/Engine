#include "SmileEnginePCH.h"
#include "C_Tile.h"
#include "C_Render.h"

dae::C_Tile::C_Tile(GameObject* pGameObject)
	: Component(pGameObject)
	, m_Stage{ 0 }
	, m_MaxStage{ 1 }
{
	m_pRenderComponent = pGameObject->GetComponent<C_Render>();
	if (m_pRenderComponent)
	{
		m_pRenderComponent->SetTexture("tile_blue.png");
	}
	else
	{
		std::cout << "Failed to initialize Tile component > Tile has no render component" << std::endl;
	}
}

void dae::C_Tile::SetMaxStage(int maxStage)
{
	m_MaxStage = maxStage;
}

bool dae::C_Tile::UpdateTile()
{
	if (m_Stage < m_MaxStage)
	{
		++m_Stage;
		UpdateTexture();
		return true;
	}

	return false;
}

void dae::C_Tile::RevertTile()
{
	if (m_Stage > 0)
	{
		--m_Stage;
		UpdateTexture();
	}
}

void dae::C_Tile::UpdateTexture()
{
	switch (m_Stage)
	{
	case 0:
		m_pRenderComponent->SetTexture("tile_blue.png");
		break;
	case 1:
		m_pRenderComponent->SetTexture("tile_yellow.png");
		break;
	case 2:
		m_pRenderComponent->SetTexture("tile_red.png");
		break;
	}
}

int dae::C_Tile::GetStage() const
{
	return m_Stage;
}

int dae::C_Tile::GetMaxStage() const
{
	return m_MaxStage;
}
