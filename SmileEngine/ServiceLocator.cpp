#include "SmileEnginePCH.h"
#include "ServiceLocator.h"

dae::NullSoundSystem dae::ServiceLocator::m_NullSoundSystem{};
dae::SoundSystem* dae::ServiceLocator::m_pSoundSystem{ &dae::ServiceLocator::m_NullSoundSystem };

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_pSoundSystem;
}

void dae::ServiceLocator::RegisterSoundSystem(SoundSystem* pSoundSystem)
{
	if (pSoundSystem)
	{
		m_pSoundSystem = pSoundSystem;
	}
	else
	{
		m_pSoundSystem = &m_NullSoundSystem;
	}
}
