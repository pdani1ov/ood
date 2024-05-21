#pragma once

#include "IShapeStrategy.h"

class CRectangleStrategy : public IShapeStrategy
{
public:
	CRectangleStrategy(const Point& startPoint, const double width, const double height)
		: m_topLeft(startPoint),
		m_width(width),
		m_height(height)
	{}

	std::string GetShapeInfo() const override
	{
		return std::to_string(m_topLeft.x)
			+ " " + std::to_string(m_topLeft.y)
			+ " " + std::to_string(m_width)
			+ " " + std::to_string(m_height);
	}

	void Move(const Point& point) override
	{
		m_topLeft.x += point.x;
		m_topLeft.y += point.y;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.MoveTo(m_topLeft);
		canvas.LineTo({ m_topLeft.x, m_topLeft.y + m_height });
		canvas.LineTo({ m_topLeft.x + m_width, m_topLeft.y });

		canvas.MoveTo({ m_topLeft.x + m_width, m_topLeft.y + m_height });
		canvas.LineTo({ m_topLeft.x, m_topLeft.y + m_height });
		canvas.LineTo({ m_topLeft.x + m_width, m_topLeft.y });
	}

	std::string GetShapeType() const override
	{
		return "rectangle";
	}
private:
	Point m_topLeft;
	double m_width;
	double m_height;
};