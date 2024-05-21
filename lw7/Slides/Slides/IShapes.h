#pragma once

#include "IShape.h"

class IShapes
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual void InsertShape(const std::shared_ptr<IShape>& shape, const size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) const = 0;
	virtual void RemoveShapeAtIndex(const size_t index) = 0;

	virtual ~IShapes() = default;
};