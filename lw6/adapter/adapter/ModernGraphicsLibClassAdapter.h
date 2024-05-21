#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class CModernGraphicsLibClassAdapter: public graphics_lib::ICanvas, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CModernGraphicsLibClassAdapter(std::ostream& out)
		:CModernGraphicsRenderer(out),
		m_start(0, 0)
	{}

	void MoveTo(int x, int y) override
	{
		m_start.x = x;
		m_start.y = y;
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);
		DrawLine(m_start, end);
		m_start = end;
	}
private:
	modern_graphics_lib::CPoint m_start;
};