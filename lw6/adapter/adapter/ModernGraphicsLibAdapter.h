#pragma once
#include "modern_graphics_lib.h"
#include "graphics_lib.h"

class CModernGraphicsLibAdapter : public graphics_lib::ICanvas
{
public:
	CModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
		: m_start(0, 0)
		, m_renderer(renderer)
	{}

	void MoveTo(int x, int y) override
	{
		m_start.x = x;
		m_start.y = y;
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);
		m_renderer.DrawLine(m_start, end);
		m_start = end;
	}
private:
	modern_graphics_lib::CPoint m_start;
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
};