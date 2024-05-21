#pragma once
#include "InputDataStreamDecorator.h"

class CDecompress : public CInputDataStreamDecorator
{
public:
	CDecompress(IInputDataStreamPtr&& stream)
		:CInputDataStreamDecorator(std::move(stream))
	{}

	bool IsEOF() const override
	{
		return CInputDataStreamDecorator::IsEOF();
	}

	uint8_t ReadByte() override
	{
		ReadCompressedBlock();
		m_lastCompressedCount--;
		return m_lastCompressedValue;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		std::streamsize readCount = 0;
		uint8_t* uncompressData = static_cast<uint8_t*>(dstBuffer);

		try
		{
			ReadCompressedBlock();
		}
		catch (...)
		{
			return 0;
		}

		while (m_lastCompressedCount != 0 && readCount < size)
		{
			try
			{
				uncompressData[readCount] = ReadByte();
				readCount++;
			}
			catch (const std::ios_base::failure&)
			{
				return readCount;
			}
		}

		return readCount;
	}

private:
	void ReadCompressedBlock()
	{
		if (m_lastCompressedCount == 0)
		{
			m_lastCompressedCount = CInputDataStreamDecorator::ReadByte();
			m_lastCompressedValue = CInputDataStreamDecorator::ReadByte();
		}
	}

	uint8_t m_lastCompressedValue = 0;
	uint8_t m_lastCompressedCount = 0;
};