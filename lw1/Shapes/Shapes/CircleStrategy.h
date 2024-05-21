#pragma once

#include "IShapeStrategy.h"

class CCircleStrategy : public IShapeStrategy
{
public:
	CCircleStrategy(const Point& center, const double radius)
		: m_center(center),
		m_radius(radius)
	{}

	std::string GetShapeInfo() const override
	{
		return std::to_string(m_center.x)
			+ " " + std::to_string(m_center.y)
			+ " " + std::to_string(m_radius);
	}

	void Move(const Point& point) override
	{
		m_center.x += point.x;
		m_center.y += point.y;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawEllipse(m_center, m_radius, m_radius);
	}

	std::string GetShapeType() const override
	{
		return "circle";
	}
private:
	Point m_center;
	double m_radius;
};