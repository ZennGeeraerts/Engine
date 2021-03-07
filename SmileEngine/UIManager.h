#pragma once
#include "Singleton.h"

struct SDL_Window;

namespace dae
{
	class UILayer;

	class UIManager final : public Singleton<UIManager>
	{
	public:
		~UIManager();
		void Render();

		void AddUILayer(UILayer* pUI);
		void RemoveUILayer(UILayer* pUI);
		void RemoveUILayer(const std::string& name);

	private:
		std::vector<UILayer*> m_pUILayers;
	};
}

