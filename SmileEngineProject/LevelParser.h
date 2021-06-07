#pragma once
#include <string>
#include <vector>
#include "glm/glm.hpp"

namespace dae
{
	class LevelParser final
	{
	public:
		bool ReadLevel(const std::string& path, std::vector<glm::vec3>& tilePositions);
		void WriteLevel(const std::string& path, const std::vector<glm::vec3>& tilePositions);
		bool ReadLevelBin(const std::string& path, std::vector<glm::vec3>& tilePositions);
		void WriteLevelBin(const std::string& path, const std::vector<glm::vec3>& tilePositions);
	};
}
