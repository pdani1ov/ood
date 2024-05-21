#pragma once
#include <string>
#include <memory>
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	virtual void Draw(ICanvas&) const = 0;

	Color GetColor() const
	{
		return m_color;
	}

	virtual ~CShape()
	{}

protected:
	CShape(Color color = DEFAULT_COLOR)
		: m_color(color)
	{}

private:
	Color m_color;
};

using ShapePtr = std::shared_ptr<CShape>;