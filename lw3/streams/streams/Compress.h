#pragma once
#include "OutputDataStreamDecorator.h"

class CCompress : public COutputDataStreamDecorator
{
public:
	CCompress(IOutputDataStreamPtr&& stream)
		:COutputDataStreamDecorator(std::move(stream))
	{}

	~CCompress()
	{
		try
		{
			Clear();
		}
		catch (...)
		{}
	}


	void WriteByte(uint8_t data) override
	{
		if (m_lastCompressedCount != 0 && m_lastCompressedValue != data)
		{
			Clear();
		}

		m_lastCompressedValue = data;
		m_lastCompressedCount++;

		if (m_lastCompressedCount == 255)
		{
			Clear();
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* data = static_cast<const uint8_t*>(srcData);

		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(data[i]);
		}
	}

	void Close() override
	{
		Clear();
		COutputDataStreamDecorator::Close();
	}
private:
	void Clear()
	{
		if (m_lastCompressedCount != 0)
		{
			COutputDataStreamDecorator::WriteByte(m_lastCompressedCount);
			COutputDataStreamDecorator::WriteByte(m_lastCompressedValue);
			m_lastCompressedCount = 0;
		}
	}

	uint8_t m_lastCompressedValue = 0;
	uint8_t m_lastCompressedCount = 0;
};