#pragma once
#include <string>
#include "AbstractCommand.h"

class CSetTextCommand : public CAbstractCommand
{
public:
	CSetTextCommand(std::string& currValue, std::string const& newValue)
		: m_currValue(currValue), 
		m_newValue(newValue)
	{}
protected:
	void DoExecute() override
	{
		std::string temp = m_currValue;
		m_currValue = m_newValue;
		m_newValue = temp;
	}

	void DoUnexecute() override
	{
		std::string temp = m_currValue;
		m_currValue = m_newValue;
		m_newValue = temp;
	}
private:
	std::string m_newValue;
	std::string& m_currValue;
};