#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureRenderer final : public Component
	{
	public:
		TextureRenderer(GameObject* pGameObject);
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

