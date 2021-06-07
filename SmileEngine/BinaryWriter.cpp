#include "SmileEnginePCH.h"
#include "BinaryWriter.h"

void BinaryWriter::WriteString(const std::string& fileName, const std::string& data)
{
	std::ofstream ofStream;
	size_t size{ data.size() };

	ofStream.open(fileName, std::ios::out | std::ios::binary | std::ios_base::app);
	if (ofStream.is_open())
	{
		ofStream.write((const char*)&size, sizeof(size));
		ofStream.write(&data[0], size);
		ofStream.close();
	}
}