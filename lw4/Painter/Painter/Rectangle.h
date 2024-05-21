#pragma once
#include "CShape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
	CRectangle()
		:m_leftTop(0, 0),
		m_rightBottom(1, 1)
	{}

	CRectangle(Point const& leftTop, Point const& rightBottom, Color color = DEFAULT_COLOR)
		:CShape(color),
		m_leftTop(leftTop),
		m_rightBottom(rightBottom)
	{}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());

		Point rightTop(m_rightBottom.x, m_leftTop.y);
		Point leftBottom(m_leftTop.x, m_rightBottom.y);

		canvas.DrawLine(m_leftTop, rightTop);
		canvas.DrawLine(rightTop, m_rightBottom);
		canvas.DrawLine(m_rightBottom, leftBottom);
		canvas.DrawLine(leftBottom, m_leftTop);
	}

	Point GetLeftTop() const
	{
		return m_leftTop;
	}

	Point GetRightBottom() const
	{
		return m_rightBottom;
	}

private:
	Point m_leftTop;
	Point m_rightBottom;
};