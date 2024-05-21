#pragma once
#include "OutputDataStream.h"
#include <fstream>

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(const std::string& filename)
		:m_file(filename, std::ios_base::out | std::ios::binary)
	{
		if (!m_file.is_open())
		{
			throw std::ios_base::failure("Failed to open file");
		}
	}

	void WriteByte(uint8_t data) override
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File is closed!");
		}

		m_file << data;
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File is closed!");
		}

		if (srcData == nullptr)
		{
			throw std::ios_base::failure("Null pointer exception");
		}

		const char* data = static_cast<const char*>(srcData);

		m_file.write(data, size);
	}

	void Close() override
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File is already closed!");
		}

		m_file.close();
	}

private:
	std::ofstream m_file;
};