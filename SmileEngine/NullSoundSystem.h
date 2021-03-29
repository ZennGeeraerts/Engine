#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	public:
		void Play(const int id, const float volume, const std::string fileName) override;
	};
}

