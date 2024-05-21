#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <optional>
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items, size_t pos)
		:m_items(items),
		m_pos(pos)
	{
		if (pos >= m_items.size())
		{
			throw std::logic_error("Incorrect position of the object to be deleted");
		}
		m_removeItem = m_items[pos];
	}

	~CDeleteItemCommand()
	{
		std::shared_ptr<IImage> image = m_removeItem->GetImage();

		if (image != nullptr && IsExecuted())
		{
			std::filesystem::remove(image->GetPath().c_str());
		}
	}
protected:
	void DoExecute() override
	{
		auto it = std::find(m_items.begin(), m_items.end(), m_removeItem);
		m_items.erase(it);
	}

	void DoUnexecute() override
	{
		m_items.insert(m_items.begin() + m_pos, m_removeItem);
	}
private:
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	std::shared_ptr<CDocumentItem> m_removeItem;
	size_t m_pos;
};