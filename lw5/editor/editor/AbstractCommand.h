#pragma once
#include "ICommand.h"

class CAbstractCommand : public ICommand
{
public:
	void Execute() final
	{
		if (!IsExecuted())
		{
			DoExecute();
			m_executed = true;
		}
	}

	void Unexecute() final
	{
		if (IsExecuted())
		{
			DoUnexecute();
			m_executed = false;
		}
	}

protected:
	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;

	bool IsExecuted() const
	{
		return m_executed;
	}

private:
	bool m_executed = false;
};