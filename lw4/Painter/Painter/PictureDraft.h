#pragma once
#include <vector>
#include <stdexcept>
#include "CShape.h"

class CPictureDraft
{
public:
	CPictureDraft()
	{}

	void AddShape(ShapePtr&& shape)
	{
		m_shapes.push_back(std::move(shape));
	}

	unsigned GetShapeCount() const
	{
		return m_shapes.size();
	}

	ShapePtr GetShape(unsigned index) const
	{
		if (index >= m_shapes.size())
		{
			throw std::invalid_argument("incorrect index of shape");
		}

		return m_shapes[index];
	}
private:
	std::vector<ShapePtr> m_shapes;
};