#pragma once
#include "Component.h"
#include "TextureRenderer.h"

namespace dae
{
	class Font;
	class Texture2D;
	class Text final : public Component
	{
	public:
		Text(GameObject* pGameObject);
		virtual ~Text() = default;
		Text(const Text & other) = delete;
		Text(Text && other) = delete;
		Text& operator=(const Text & other) = delete;
		Text& operator=(Text && other) = delete;

		void Update() override;

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		TextureRenderer* m_pTextureRenderer;
	};
}
