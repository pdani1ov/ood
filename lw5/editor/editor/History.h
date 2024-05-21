#pragma once
#include <vector>
#include <memory>
#include "ICommand.h"

class CHistory 
{
public:

	bool CanUndo() const
	{
		return m_actionIndex != 0;
	}

	void Undo() {
		if (CanUndo())
		{
			m_history[--m_actionIndex]->Unexecute();
		}
	}

	bool CanRedo() const
	{
		return m_actionIndex != m_history.size();
	}

	void Redo()
	{
		if (CanRedo())
		{
			m_history[m_actionIndex++]->Execute();
		}
	}

	void AddAndExecuteCommand(std::shared_ptr<ICommand> command)
	{
		if (m_actionIndex < m_history.size())
		{
			command->Execute();
			m_history.erase(m_history.begin() + m_actionIndex, m_history.end());
			m_actionIndex++;
			m_history.push_back(command);
		}
		else
		{
			command->Execute();
			m_history.push_back(command);
			if (m_actionIndex > MAX_HISTORY_SIZE - 1)
			{
				m_history.erase(m_history.begin());
			}
			else
			{
				m_actionIndex++;
			}
		}
	}

private:
	const size_t MAX_HISTORY_SIZE = 10;
	std::vector<std::shared_ptr<ICommand>> m_history;
	size_t m_actionIndex = 0;
};