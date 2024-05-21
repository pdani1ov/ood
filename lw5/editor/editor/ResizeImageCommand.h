#pragma once
#include "AbstractCommand.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& currHeight, int& currWidth, int newHeight, int newWidth)
		:m_currHeight(currHeight),
		m_currWidth(currWidth),
		m_newHeight(newHeight),
		m_newWidth(newWidth)
	{}
protected:
	void DoExecute() override
	{
		int tempWidth = m_currWidth;
		int tempHeight = m_currHeight;
		m_currWidth = m_newWidth;
		m_currHeight = m_newHeight;
		m_newWidth = tempWidth;
		m_newHeight = tempHeight;
	}

	void DoUnexecute() override
	{
		int tempWidth = m_currWidth;
		int tempHeight = m_currHeight;
		m_currWidth = m_newWidth;
		m_currHeight = m_newHeight;
		m_newWidth = tempWidth;
		m_newHeight = tempHeight;
	}
private:
	int& m_currWidth;
	int& m_currHeight;
	int m_newWidth;
	int m_newHeight;
};