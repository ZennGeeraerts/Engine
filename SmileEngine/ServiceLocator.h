#pragma once
#include "SoundSystem.h"
#include "NullSoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(SoundSystem* pSoundSystem);

	private:
		static NullSoundSystem m_NullSoundSystem;
		static SoundSystem* m_pSoundSystem;
	};
}

