#pragma once
#include "Cryptographer.h"
#include "OutputDataStreamDecorator.h"

class CEncrypt : public COutputDataStreamDecorator
{
public:
	CEncrypt(IOutputDataStreamPtr&& stream, uint32_t key)
		:COutputDataStreamDecorator(std::move(stream)),
		m_crypt(CCryptographer(key))
	{}

	void WriteByte(uint8_t data) override
	{
		uint8_t encryptData = m_crypt.Encrypt(data);
		COutputDataStreamDecorator::WriteByte(encryptData);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		std::vector<uint8_t> encryptData;
		encryptData.resize(static_cast<unsigned>(size));
		const uint8_t* data = static_cast<const uint8_t*>(srcData);

		for (int i = 0; i < size; i++)
		{
			encryptData[i] = m_crypt.Encrypt(data[i]);
		}

		COutputDataStreamDecorator::WriteBlock(&encryptData[0], size);
	}

	void Close() override
	{
		COutputDataStreamDecorator::Close();
	}
private:
	CCryptographer m_crypt;
};