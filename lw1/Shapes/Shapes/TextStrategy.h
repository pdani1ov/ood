#pragma once

#include "IShapeStrategy.h"

class CTextStrategy : public IShapeStrategy
{
public:
	CTextStrategy(const Point& startPoint, const double fontSize, const std::string& text)
		: m_topLeft(startPoint),
		m_fontSize(fontSize),
		m_text(text)
	{}

	std::string GetShapeInfo() const override
	{
		return std::to_string(m_topLeft.x)
			+ " " + std::to_string(m_topLeft.y)
			+ " " + std::to_string(m_fontSize)
			+ " " + m_text;
	}

	void Move(const Point& point) override
	{
		m_topLeft.x += point.x;
		m_topLeft.y += point.y;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawText(m_topLeft, m_fontSize, m_text);
	}

	std::string GetShapeType() const override
	{
		return "text";
	}
private:
	Point m_topLeft;
	double m_fontSize;
	std::string m_text;
};