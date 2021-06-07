#include "SmileEnginePCH.h"
#include "LevelParser.h"
#include <fstream>
#include <sstream>
#include "BinaryWriter.h"
#include "BinaryReader.h"

bool dae::LevelParser::ReadLevel(const std::string& path, std::vector<glm::vec3>& tilePositions)
{
	std::ifstream ifStream{};
	std::string sign{};
	std::string text{};

	ifStream.open(path, std::ios::in);

	if (!ifStream.is_open())
	{
		return false;
	}

	while (!ifStream.eof())
	{
		std::getline(ifStream, text, '\n');
		std::istringstream stringStream{ text };
		std::getline(stringStream, sign, ' ');
		std::getline(stringStream, text, '\n');

		if (sign != "")
		{
			// remove spaces from text
			std::string textCopy{ text };
			for (size_t i{}; i < text.size(); ++i)
			{
				if (text[i] != ' ')
				{
					break;
				}
				textCopy = textCopy.substr(1, textCopy.size() - 1);
			}
			text = textCopy;

			if (sign == "pos")
			{
				glm::vec3 pos{};
				std::istringstream inputStream{ text };

				std::getline(inputStream, text, ' ');
				pos.x = std::stof(text);

				std::getline(inputStream, text, ' ');
				pos.y = std::stof(text);

				std::getline(inputStream, text, '\n');
				pos.z = std::stof(text);

				tilePositions.push_back(pos);
			}
		}
	}

	ifStream.close();
	return true;
}

void dae::LevelParser::WriteLevel(const std::string& path, const std::vector<glm::vec3>& tilePositions)
{
	std::ofstream ofStream{};

	ofStream.open(path, std::ios::out);
	if (!ofStream.is_open())
	{
		std::cout << "Couldn't open file: " << path << std::endl;
		return;
	}

	for (const auto& tilePos : tilePositions)
	{
		ofStream << "pos " << tilePos.x << ' ' << tilePos.y << ' ' << tilePos.z << '\n';
	}

	ofStream.close();
}

bool dae::LevelParser::ReadLevelBin(const std::string& path, std::vector<glm::vec3>& tilePositions)
{
	BinaryReader binReader{ path };
	std::string sign{};
	std::string text{};

	if (!binReader.IsOpen())
	{
		return false;
	}

	while (!binReader.EndOfFile())
	{
		sign = binReader.ReadString();

		if (sign != "")
		{
			if (sign == "pos")
			{
				float posX = binReader.ReadData<float>();
				float posY = binReader.ReadData<float>();
				float posZ = binReader.ReadData<float>();
				tilePositions.push_back(glm::vec3{ posX, posY, posZ });
			}

			binReader.ReadData<char>();
		}
	}

	binReader.Close();
	return true;
}

void dae::LevelParser::WriteLevelBin(const std::string& path, const std::vector<glm::vec3>& tilePositions)
{
	std::ofstream ofStream{};

	ofStream.open(path, std::ios::out | std::ios::binary);
	if (!ofStream.is_open())
	{
		std::cout << "Couldn't open file: " << path << std::endl;
		return;
	}

	for (const auto& tilePos : tilePositions)
	{
		BinaryWriter::WriteString(path, "pos");
		BinaryWriter::WriteData<float>(path, tilePos.x);
		BinaryWriter::WriteData<float>(path, tilePos.y);
		BinaryWriter::WriteData<float>(path, tilePos.z);
		BinaryWriter::WriteData<char>(path, '\n');
	}

	ofStream.close();
}