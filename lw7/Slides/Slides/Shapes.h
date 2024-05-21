#pragma once
#include <vector>
#include <stdexcept>

#include "IShapes.h"

class CShapes : public IShapes
{
public:
	size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	void InsertShape(const std::shared_ptr<IShape>& shape, const size_t position = std::numeric_limits<size_t>::max()) override
	{
		if (position >= m_shapes.size())
		{
			m_shapes.insert(m_shapes.end(), shape);
			return;
		}
		m_shapes.insert(m_shapes.begin() + position, shape);
	}

	std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) const override
	{
		return m_shapes.at(index);
	}

	void RemoveShapeAtIndex(const size_t index) override
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Invalid index");
		}
		m_shapes.erase(m_shapes.begin() + index);
	}
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};