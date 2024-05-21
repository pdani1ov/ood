#pragma once
#include "OutputDataStream.h"
#include <vector>

class CMemoryOutputStream : public IOutputDataStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t>& output)
		:m_output(output)
	{}

	void WriteByte(uint8_t data) override
	{
		if (m_isClosed)
		{
			throw std::logic_error("File is closed!");
		}

		m_output.push_back(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (m_isClosed)
		{
			throw std::logic_error("File is closed!");
		}

		if (srcData == nullptr)
		{
			throw std::ios_base::failure("Null pointer exception");
		}

		const uint8_t* data = static_cast<const uint8_t*>(srcData);

		for (unsigned i = 0; i < size; i++)
		{
			m_output.push_back(data[i]);
		}
	}

	void Close() override
	{
		if (!m_isClosed)
		{
			m_isClosed = true;
		}
		else
		{
			throw std::logic_error("File is already closed!");
		}
	}

private:
	std::vector<uint8_t>& m_output;
	bool m_isClosed = false;
};