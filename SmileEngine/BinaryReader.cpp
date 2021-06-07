#include "SmileEnginePCH.h"
#include "BinaryReader.h"

dae::BinaryReader::BinaryReader(const std::string& path)
	: m_InputFileStream{}
	, m_FilePath{ path }
{
	m_InputFileStream.open(m_FilePath, std::ios::in | std::ios::binary);
}

std::string dae::BinaryReader::ReadString()
{
	std::string data{};
	size_t size{};

	if (m_InputFileStream.is_open())
	{
		m_InputFileStream.read((char*)&size, sizeof(size));
		data.resize(size);
		m_InputFileStream.read(&data[0], size);
	}

	return data;
}

bool dae::BinaryReader::IsOpen() const
{
	return m_InputFileStream.is_open();
}

bool dae::BinaryReader::EndOfFile() const
{
	return m_InputFileStream.eof();
}

void dae::BinaryReader::Close()
{
	m_InputFileStream.close();
}