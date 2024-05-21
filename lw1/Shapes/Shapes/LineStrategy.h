#pragma once

#include "IShapeStrategy.h"

class CLineStrategy : public IShapeStrategy
{
public:
	CLineStrategy(const Point& startPoint, const Point& endPoint)
		: m_startPoint(startPoint),
		m_endPoint(endPoint)
	{}

	std::string GetShapeInfo() const override
	{
		return std::to_string(m_startPoint.x)
			+ " " + std::to_string(m_startPoint.y)
			+ " " + std::to_string(m_endPoint.x)
			+ " " + std::to_string(m_endPoint.y);
	}

	void Move(const Point& point) override
	{
		m_startPoint.x += point.x;
		m_startPoint.y += point.y;
		m_endPoint.x += point.x;
		m_endPoint.y += point.y;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.MoveTo(m_startPoint);
		canvas.LineTo(m_endPoint);
	}

	std::string GetShapeType() const override
	{
		return "line";
	}
private:
	Point m_startPoint;
	Point m_endPoint;
};