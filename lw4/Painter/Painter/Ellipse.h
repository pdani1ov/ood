#pragma once
#include "CShape.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	CEllipse(Point const& center, unsigned verticalRadius, unsigned horizontalRadius, Color color = DEFAULT_COLOR)
		:CShape(color),
		m_center(center),
		m_verticalRadius(verticalRadius),
		m_horizontalRadius(horizontalRadius)
	{}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());

		Point leftTop(m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius);

		canvas.DrawEllipse(leftTop, 2 * m_horizontalRadius, 2 * m_verticalRadius);
	}

	Point GetCenter()
	{
		return m_center;
	}

	unsigned GetVerticalRadius()
	{
		return m_verticalRadius;
	}

	unsigned GetHorizontalRadius()
	{
		return m_horizontalRadius;
	}
private:
	Point m_center;
	unsigned m_verticalRadius;
	unsigned m_horizontalRadius;
};