#pragma once

#include "IShapeStrategy.h"

class CTriangleStrategy : public IShapeStrategy
{
public:
	CTriangleStrategy(const Point& point1, const Point& point2, const Point& point3)
		: m_point1(point1)
		, m_point2(point2)
		, m_point3(point3)
	{}

	std::string GetShapeInfo() const override
	{
		std::string result = "";

		result += " " + std::to_string(m_point1.x)
			+ " " + std::to_string(m_point1.y)
			+ " " + std::to_string(m_point2.x)
			+ " " + std::to_string(m_point2.y)
			+ " " + std::to_string(m_point3.x)
			+ " " + std::to_string(m_point3.y);

		return result;
	}

	void Move(const Point& point) override
	{
		m_point1.x += point.x;
		m_point1.y += point.y;
		m_point2.x += point.x;
		m_point2.y += point.y;
		m_point3.x += point.x;
		m_point3.y += point.y;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.MoveTo(m_point1);
		canvas.LineTo(m_point2);
		canvas.MoveTo(m_point2);
		canvas.LineTo(m_point3);
		canvas.MoveTo(m_point3);
		canvas.LineTo(m_point1);
	}

	std::string GetShapeType() const override
	{
		return "triangle";
	}
private:

	Point m_point1;
	Point m_point2;
	Point m_point3;
};