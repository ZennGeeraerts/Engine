#pragma once
namespace dae
{
	struct PlaySound
	{
		PlaySound(int id, float volume, const std::string& filePath)
			: id{ id }
			, volume{ volume }
			, filePath{ filePath }
		{}

		int id;
		float volume;
		std::string filePath;
	};

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const int id, const float volume, const std::string fileName) = 0;
	};
}

