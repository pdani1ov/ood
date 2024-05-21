#pragma once
#include "InputDataStreamDecorator.h"
#include "Cryptographer.h"

class CDecrypt : public CInputDataStreamDecorator
{
public:
	CDecrypt(IInputDataStreamPtr&& stream, uint32_t key)
		:CInputDataStreamDecorator(std::move(stream)),
		m_crypt(CCryptographer(key))
	{}

	bool IsEOF() const override
	{
		return CInputDataStreamDecorator::IsEOF();
	}

	uint8_t ReadByte() override
	{
		uint8_t data = CInputDataStreamDecorator::ReadByte();
		return m_crypt.Decrypt(data);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		std::streamsize readSize = CInputDataStreamDecorator::ReadBlock(dstBuffer, size);
		uint8_t* data = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < readSize; i++)
		{
			data[i] = m_crypt.Decrypt(data[i]);
		}
		std::cout << std::endl;
		return readSize;
	}

	void Close() override
	{
		return CInputDataStreamDecorator::Close();
	}
private:
	CCryptographer m_crypt;
};