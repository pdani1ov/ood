#pragma once
#include "InputDataStream.h"
#include <vector>

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& input)
		: m_input(input)
	{}

	bool IsEOF() const override
	{
		if (m_isClosed)
		{
			throw std::logic_error("File is closed!");
		}

		return m_input.empty();
	}

	uint8_t ReadByte() override
	{
		if (m_isClosed)
		{
			throw std::logic_error("File is closed!");
		}

		uint8_t byte = *m_input.begin();
		m_input.erase(m_input.begin());

		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (m_isClosed)
		{
			throw std::logic_error("File is closed!");
		}

		unsigned realReadBytes = 0;
		uint8_t* data = static_cast<uint8_t*>(dstBuffer);

		if (data == nullptr)
		{
			throw std::ios_base::failure("Null pointer exception");
		}

		for (unsigned i = 0; i < size; i++)
		{
			if (IsEOF())
			{
				break;
			}

			data[i] = ReadByte();
			realReadBytes++;
		}

		return realReadBytes;
	}

	void Close() override
	{
		if (m_isClosed)
		{
			throw std::logic_error("File is already closed!");
		}
		m_isClosed = true;
	}
private:
	std::vector<uint8_t>& m_input;
	bool m_isClosed = false;
};