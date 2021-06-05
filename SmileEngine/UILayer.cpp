#include "SmileEnginePCH.h"
#include "UILayer.h"

dae::UILayer::UILayer(const glm::vec2& pos, const std::string& name)
	: m_Name{ name }
	, m_Position{ pos }
{
	
}

const std::string& dae::UILayer::GetName() const
{
	return m_Name;
}
