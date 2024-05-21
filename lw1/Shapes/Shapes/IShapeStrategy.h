#pragma once

#include "Point.h"
#include "ICanvas.h"

class IShapeStrategy
{
public:
	virtual void Move(const Point& point) = 0;
	virtual std::string GetShapeInfo() const = 0;
	virtual std::string GetShapeType() const = 0;
	virtual void Draw(ICanvas& canvas) const = 0;
};