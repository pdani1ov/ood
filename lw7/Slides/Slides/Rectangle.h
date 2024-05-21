#pragma once
#include <stdexcept>

#include "Shape.h"
#include "CommonTypes.h"

class CRectangle : public CShape
{
public:
	CRectangle(
		const Point& leftTop,
		const double width,
		const double height,
		const std::shared_ptr<CLineStyle> lineStyle,
		const std::shared_ptr<CColorStyle> colorStyle
	)
		:CShape(lineStyle, colorStyle)
		,m_leftTop(leftTop)
	{
		if (width <= 0)
		{
			throw std::out_of_range("Inavalid width");
		}
		m_width = width;

		if (height <= 0)
		{
			throw std::out_of_range("Inavalid height");
		}
		m_height = height;
	}

	CRectangle(
		const RectD& rect,
		const std::shared_ptr<CLineStyle> lineStyle,
		const std::shared_ptr<CColorStyle> colorStyle
	)
		:CShape(lineStyle, colorStyle)
		, m_leftTop({ rect.left, rect.top })
	{
		if (rect.width <= 0)
		{
			throw std::out_of_range("Inavalid width");
		}
		m_width = rect.width;

		if (rect.height <= 0)
		{
			throw std::out_of_range("Inavalid height");
		}
		m_height = rect.height;
	}

	std::optional<RectD> GetFrame() const override
	{
		RectD rect;
		rect.left = m_leftTop.x;
		rect.top = m_leftTop.y;
		rect.width = m_width;
		rect.height = m_height;

		return rect;
	}

	void SetFrame(const RectD& rect) override
	{
		m_leftTop.x = rect.left;
		m_leftTop.y = rect.top;

		if (rect.width <= 0)
		{
			throw std::out_of_range("Inavalid width");
		}
		m_width = rect.width;

		if (rect.height <= 0)
		{
			throw std::out_of_range("Inavalid height");
		}
		m_height = rect.height;
	}

	void Draw(ICanvas& canvas) const override
	{
		auto lineStyleColor = GetOutlineStyle()->GetColor();
		canvas.SetLineColor(lineStyleColor.has_value() ? lineStyleColor.value() : 0x000000);
		auto fillStyleColor = GetFillStyle()->GetColor();
		if (fillStyleColor.has_value())
		{
			canvas.BeginFill(fillStyleColor.value());
		}

		canvas.SetLineWidth(GetOutlineStyle()->GetWidth());

		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);

		canvas.EndFill();
	}
private:
	Point m_leftTop;
	double m_width;
	double m_height;
};