#pragma once
#include "CShape.h"
#include "Point.h"

class CTriangle : public CShape
{
public:
	CTriangle(Point const& vertex1, Point const& vertex2, Point const& vertex3, Color color = DEFAULT_COLOR)
		:CShape(color),
		m_vertex1(vertex1),
		m_vertex2(vertex2),
		m_vertex3(vertex3)
	{}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());

		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}

	Point GetVertex1() const
	{
		return m_vertex1;
	}

	Point GetVertex2() const
	{
		return m_vertex2;
	}

	Point GetVertex3() const
	{
		return m_vertex3;
	}
private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};