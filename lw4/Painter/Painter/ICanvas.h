#pragma once
#include "Point.h"
#include "Color.h"

//сделать ICanvas по заданию
class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawEllipse(Point leftTop, unsigned width, unsigned height) = 0;

	virtual ~ICanvas() = default;
};