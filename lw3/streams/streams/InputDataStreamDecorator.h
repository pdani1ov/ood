#pragma once
#include "InputDataStream.h"

class CInputDataStreamDecorator : public IInputDataStream
{
public:
	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_stream->ReadByte();
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		return m_stream->ReadBlock(dstBuffer, size);
	}

	void Close() override
	{
		m_stream->Close();
	}
protected:
	CInputDataStreamDecorator(IInputDataStreamPtr&& stream)
		:m_stream(std::move(stream))
	{}
private:
	IInputDataStreamPtr m_stream;
};