#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;

	class C_Render final : public Component
	{
	public:
		C_Render(GameObject* pGameObject);
		virtual ~C_Render() noexcept = default;

		C_Render(const C_Render& other) = delete;
		C_Render(C_Render&& other) noexcept = delete;
		C_Render& operator=(const C_Render& other) = delete;
		C_Render& operator=(C_Render&& other) = delete;

		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);
		std::shared_ptr<Texture2D> GetTexture() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

