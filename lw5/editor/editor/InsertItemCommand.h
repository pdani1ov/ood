#pragma once
#include <vector>
#include <memory>
#include <optional>
#include "DocumentItem.h"
#include "AbstractCommand.h"

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items, std::shared_ptr<CDocumentItem> value, std::optional<size_t> pos)
		:m_items(items),
		m_value(value),
		m_pos(pos)
	{}

	~CInsertItemCommand()
	{
		std::shared_ptr<IImage> image = m_value->GetImage();

		if (image != nullptr && !IsExecuted())
		{
			std::filesystem::remove(image->GetPath().c_str());
		}
	}
protected:
	void DoExecute() override
	{	
		if (m_pos.has_value() && m_pos.value() < m_items.size())
		{
			m_items.insert(m_items.begin() + m_pos.value(), m_value);
		}
		else
		{
			m_items.push_back(m_value);
		}
	}

	void DoUnexecute() override
	{
		auto it = find(m_items.begin(), m_items.end(), m_value);
		m_items.erase(it);
	}
private:
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	std::shared_ptr<CDocumentItem> m_value;
	std::optional<size_t> m_pos;
};