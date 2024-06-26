#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class CModernGraphicsLibClassAdapter : public graphics_lib::ICanvas, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CModernGraphicsLibClassAdapter(std::ostream& out)
		:CModernGraphicsRenderer(out),
		m_start(0, 0),
		m_color(0, 0, 0, 1)
	{}

	void SetColor(uint32_t rgbColor)
	{
		m_color.r = (static_cast<float>((rgbColor >> 16) & 0xff) / 255);
		m_color.g = (static_cast<float>((rgbColor >> 8) & 0xff) / 255);
		m_color.b = (static_cast<float>((rgbColor & 0xff)) / 255);
	}

	void MoveTo(int x, int y) override
	{
		m_start.x = x;
		m_start.y = y;
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);
		DrawLine(m_start, end, m_color);
		m_start = end;
	}
private:
	modern_graphics_lib::CPoint m_start;
	modern_graphics_lib::CRGBAColor m_color;
};