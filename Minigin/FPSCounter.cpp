#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "Time.h"

using namespace std;

dae::FPSCounter::FPSCounter(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pText{ nullptr }
{
	m_pText = pGameObject->GetComponent<Text>();
	if (!m_pText)
	{
		std::cerr << "No text component found on FPSCounter" << endl;
	}
}

void dae::FPSCounter::Update()
{
	if (!m_pText)
	{
		return;
	}

	auto& time{ Time::GetInstance() };
	std::string text{ std::to_string(time.GetFPS()) + " FPS" };
	m_pText->SetText(text);
}
