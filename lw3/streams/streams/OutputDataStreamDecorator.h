#pragma once
#include "OutputDataStream.h"

class COutputDataStreamDecorator : public IOutputDataStream
{
public:
	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_stream->WriteBlock(srcData, size);
	}

	void Close() override
	{
		m_stream->Close();
	}
protected:
	COutputDataStreamDecorator(IOutputDataStreamPtr&& stream)
		:m_stream(std::move(stream))
	{}
private:
	IOutputDataStreamPtr m_stream;
};