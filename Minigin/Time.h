#pragma once
#include <chrono>
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void Run();
	void Update();
	bool IsCatchingUpInFixedSteps();

	float GetDeltaTime() const;
	float GetTotalTimePassed() const;
	uint32_t GetFPS() const;
	void SetMsPerFrame(uint32_t msPerFrame);

private:
	friend class Singleton<Time>;
	Time();

	uint32_t m_MsPerFrame; /* amount of milliseconds per frame for the fixed update */
	float m_Lag;
	float m_TotalTimePassed;
	float m_DeltaTime;
	uint32_t m_FPS;
	std::chrono::steady_clock::time_point m_LastTime;
	bool m_IsRunning;
};

