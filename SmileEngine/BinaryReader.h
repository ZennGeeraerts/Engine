#pragma once
#include <string>
#include <fstream>

namespace dae
{
	class BinaryReader
	{
	public:
		BinaryReader(const std::string& path);

		template <class T>
		T ReadData()
		{
			T data{};

			if (m_InputFileStream.is_open())
			{
				m_InputFileStream.read((char*)&data, sizeof(data));
			}

			return data;
		}

		std::string ReadString();
		bool IsOpen() const;
		bool EndOfFile() const;
		void Close();

	private:
		std::ifstream m_InputFileStream;
		std::string m_FilePath;
	};
}
