#pragma once
#include "Component.h"

namespace dae
{
	class C_Render;

	class C_Tile final : public Component
	{
	public:
		C_Tile(GameObject* pGameObject);

		void SetMaxStage(int maxStage);

		bool UpdateTile();
		void RevertTile();
		int GetStage() const;
		int GetMaxStage() const;

	private:
		void UpdateTexture();

		int m_Stage;
		int m_MaxStage;
		C_Render* m_pRenderComponent;
	};
}

