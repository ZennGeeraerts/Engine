#pragma once
#include "Component.h"
#include "C_Render.h"

namespace dae
{
	class Font;
	class Texture2D;
	class C_Text final : public Component
	{
	public:
		C_Text(GameObject* pGameObject);
		virtual ~C_Text() = default;
		C_Text(const C_Text & other) = delete;
		C_Text(C_Text && other) = delete;
		C_Text& operator=(const C_Text & other) = delete;
		C_Text& operator=(C_Text && other) = delete;

		void Update() override;

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		C_Render* m_pRendererComponent;
	};
}
