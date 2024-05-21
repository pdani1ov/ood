#pragma once

#include "IShapeStrategy.h"

class CShape
{
public:
	CShape(std::unique_ptr<IShapeStrategy>&& shapeStrategy, const Color& color)
		: m_shapeStrategy(std::move(shapeStrategy))
		, m_color(color)
	{
	}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(m_color);
		m_shapeStrategy->Draw(canvas);
	}

	void Move(const Point& point)
	{
		m_shapeStrategy->Move(point);
	}

	std::string GetShapeInfo() const
	{
		return m_shapeStrategy->GetShapeInfo();
	}

	Color GetColor()
	{
		return m_color;
	}

	std::string GetType()
	{
		return m_shapeStrategy->GetShapeType();
	}

	void SetColor(const Color& color)
	{
		m_color = color;
	}

	void SetShapeStrategy(std::unique_ptr<IShapeStrategy>&& shapeStrategy)
	{
		m_shapeStrategy = std::move(shapeStrategy);
	}

private:
	std::unique_ptr<IShapeStrategy> m_shapeStrategy;
	Color m_color;
};