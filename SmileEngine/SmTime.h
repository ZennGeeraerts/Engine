#pragma once
#include <chrono>
#include "Singleton.h"

class SmTime final : public dae::Singleton<SmTime>
{
public:
	void Run();
	void Update();
	bool IsCatchingUpInFixedSteps();

	float GetDeltaTime() const;
	float GetTotalTimePassed() const;
	uint32_t GetFPS() const;
	void SetMsPerFrame(uint32_t msPerFrame);
	uint32_t GetMsPerFrame() const;
	std::chrono::steady_clock::time_point GetTimeBeforeGameLoop() const;
	bool GetDoContinue() const;
	void SetDoContinue(bool doContinue);

private:
	friend class Singleton<SmTime>;
	SmTime();

	uint32_t m_MsPerFrame; /* amount of milliseconds per frame for the fixed update */
	float m_Lag;
	float m_TotalTimePassed;
	float m_DeltaTime;
	uint32_t m_FPS;
	std::chrono::steady_clock::time_point m_LastTime;
	bool m_IsRunning;
	bool m_DoContinue;
};

