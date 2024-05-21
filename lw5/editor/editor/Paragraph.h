#pragma once
#include <string>
#include <memory>
#include "IParagraph.h"
#include "History.h"
#include "SetTextCommand.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(const std::string& text, CHistory& history)
		: m_text(text),
		m_history(history)
	{
	}

	std::string GetText() const override
	{
		return m_text;
	}

	void SetText(const std::string& text)override
	{
		m_history.AddAndExecuteCommand(std::make_shared<CSetTextCommand>(m_text, text));
	}

private:
	std::string m_text;
	CHistory& m_history;
};