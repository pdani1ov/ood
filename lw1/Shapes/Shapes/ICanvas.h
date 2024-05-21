#pragma once
#include <string>

#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetColor(const Color& color) = 0;

	virtual void MoveTo(const Point& point) = 0;

	virtual void LineTo(const Point& point) = 0;

	virtual void DrawEllipse(const Point& center, const double rx, const double ry) = 0;

	virtual void DrawText(const Point& point, const double fontSize, const std::string& text) = 0;
};