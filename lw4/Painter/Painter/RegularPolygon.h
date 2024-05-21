#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "CShape.h"
#include "Point.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Point const& center, unsigned radius, unsigned vertexCount, Color color = DEFAULT_COLOR)
		:CShape(color),
		m_center(center),
		m_radius(radius),
		m_vertexCount(vertexCount)
	{}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());

		Point from(m_center.x + m_radius, m_center.y);
		Point to(m_center.x, m_center.y);

		for (unsigned i = 1; i < m_vertexCount; i++)
		{
			to.x = m_center.x + m_radius * cos(2 * M_PI * i / m_vertexCount);
			to.y = m_center.y + m_radius * sin(2 * M_PI * i / m_vertexCount);

			canvas.DrawLine(from, to);

			from = to;
		}

		to.x = m_center.x + m_radius;
		to.y = m_center.y;

		canvas.DrawLine(from, to);
	}

	Point GetCenter() const
	{
		return m_center;
	}

	unsigned GetRadius() const
	{
		return m_radius;
	}

	unsigned GetVertexCount() const
	{
		return m_vertexCount;
	}

private:
	Point m_center;
	unsigned m_radius;
	unsigned m_vertexCount;
};