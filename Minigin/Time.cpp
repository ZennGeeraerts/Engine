#include "MiniginPCH.h"
#include "Time.h"

using namespace std::chrono;

Time::Time()
	: m_MsPerFrame{ 16 }
	, m_Lag{ 0.0f }
	, m_TotalTimePassed{ 0.0f }
	, m_DeltaTime{ 0.0f }
	, m_FPS{ 0 }
	, m_LastTime{}
	, m_IsRunning{ false }
{

}

void Time::Run()
{
	m_IsRunning = true;
	m_LastTime = high_resolution_clock::now();
}

void Time::Update()
{
	if (!m_IsRunning)
	{
		return;
	}

	const auto currentTime{ high_resolution_clock::now() };
	m_DeltaTime = duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
	m_Lag += m_DeltaTime;

	m_FPS = uint32_t(1.f / m_DeltaTime);
}

bool Time::IsCatchingUpInFixedSteps()
{
	if (m_Lag >= m_MsPerFrame)
	{
		m_Lag -= m_MsPerFrame;
		return true;
	}

	return false;
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

float Time::GetTotalTimePassed() const
{
	return m_TotalTimePassed;
}

uint32_t Time::GetFPS() const
{
	return m_FPS;
}

void Time::SetMsPerFrame(uint32_t msPerFrame)
{
	m_MsPerFrame = msPerFrame;
}
