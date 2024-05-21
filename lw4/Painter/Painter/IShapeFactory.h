#pragma once
#include "CShape.h"

class IShapeFactory
{
public:
	virtual ShapePtr CreateShape(std::string const& description) = 0;

	virtual ~IShapeFactory() = default;
};