#include "MiniginPCH.h"
#include "C_FPSCounter.h"
#include "Time.h"

using namespace std;

dae::C_FPSCounter::C_FPSCounter(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pText{ nullptr }
	, m_UpdateRate{ 1.f }
	, m_ElapsedSec{ 0.f }
{
	m_pText = pGameObject->GetComponent<C_Text>();
	if (!m_pText)
	{
		std::cerr << "No text component found on FPSCounter" << endl;
	}
}

void dae::C_FPSCounter::Update()
{
	if (!m_pText)
	{
		return;
	}

	auto& time{ Time::GetInstance() };

	m_ElapsedSec += time.GetDeltaTime();
	if (m_ElapsedSec > m_UpdateRate)
	{
		std::string text{ std::to_string(time.GetFPS()) + " FPS" };
		m_pText->SetText(text);
		m_ElapsedSec -= m_UpdateRate;
	}
}

void dae::C_FPSCounter::SetUpdateRate(float updateRate)
{
	m_UpdateRate = updateRate;
}
