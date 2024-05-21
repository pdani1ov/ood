#pragma once
#include <fstream>
#include "InputDataStream.h"

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(const std::string& filename)
		: m_file(filename, std::ios_base::in | std::ios::binary)
	{
		if (!m_file.is_open())
		{
			throw std::ios_base::failure("Failed to open file");
		}
	}

	bool IsEOF() const override
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File is closed!");
		}

		return m_file.eof();
	}

	uint8_t ReadByte() override
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File is closed!");
		}

		char data;
		m_file.read(&data, 1);
		return static_cast<uint8_t>(data);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File is closed!");
		}

		m_file.read(static_cast<char*>(dstBuffer), size);
		return m_file.gcount();
	}

	void Close() override
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("File is alredy closed!");
		}
		m_file.close();
	}

private:
	std::ifstream m_file;
};