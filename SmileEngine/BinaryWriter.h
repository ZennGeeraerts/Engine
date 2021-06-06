#pragma once
#include <string>
#include <fstream>
#include <iostream>

class BinaryWriter
{
public:
	template <class T>
	static void WriteData(const std::string& fileName, const T& data)
	{
		if (std::is_pod<T>::value)
		{
			std::ofstream ofStream;
			ofStream.open(fileName, std::ios::out | std::ios::binary | std::ios_base::app);
			if (ofStream.is_open())
			{
				ofStream.write((const char*)&data, sizeof(data));
				ofStream.close();
			}
		}
		else
		{
			std::cout << "Class is not a pod.\n";
		}
	}

	static void WriteString(const std::string& fileName, const std::string& data);
};

