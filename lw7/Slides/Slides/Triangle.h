#pragma once
#include <stdexcept>

#include "Shape.h"
#include "CommonTypes.h"

class CTriangle : public CShape
{
public:
	CTriangle(
		const Point& point1,
		const Point& point2,
		const Point& point3,
		const std::shared_ptr<CLineStyle> lineStyle,
		const std::shared_ptr<CColorStyle>& colorStyle
	)
		:CShape(lineStyle, colorStyle)
		, m_point1(point1)
		, m_point2(point2)
		, m_point3(point3)
	{}

	CTriangle(
		const RectD& rect,
		const std::shared_ptr<CLineStyle> lineStyle,
		const std::shared_ptr<CColorStyle>& colorStyle
	)
		:CShape(lineStyle, colorStyle)
		, m_point1({ rect.left + rect.width * 0.5, rect.top })
	{
		if (rect.width <= 0)
		{
			throw std::out_of_range("Inavalid rect width");
		}

		if (rect.height <= 0)
		{
			throw std::out_of_range("Inavalid rect height");
		}

		m_point2 = { rect.left, rect.top + rect.height };
		m_point3 = { rect.left + rect.width, rect.top + rect.height };
	}

	std::optional<RectD> GetFrame() const override
	{
		RectD rect;
		rect.left = std::min({ m_point1.x, m_point2.x, m_point3.x });
		rect.top = std::min({ m_point1.y, m_point2.y, m_point3.y });
		rect.width = std::max({ m_point1.x, m_point2.x, m_point3.x }) - rect.left;
		rect.height = std::max({ m_point1.y, m_point2.y, m_point3.y }) - rect.top;

		return rect;
	}

	void SetFrame(const RectD& rect) override
	{
		if (rect.width <= 0)
		{
			throw std::out_of_range("Inavalid rect width");
		}

		if (rect.height <= 0)
		{
			throw std::out_of_range("Inavalid rect height");
		}

		m_point1.x = rect.left + rect.width * 0.5;
		m_point1.y = rect.top;

		m_point2.x = rect.left;
		m_point2.y = rect.top + rect.height;

		m_point3.x = rect.left + rect.width;
		m_point3.y = rect.top + rect.height;
	}

	void Draw(ICanvas& canvas) const override
	{
		auto lineStyleColor = GetOutlineStyle()->GetColor();
		canvas.SetLineColor(lineStyleColor.has_value() ? lineStyleColor.value() : 0x000000);
		canvas.SetLineWidth(GetOutlineStyle()->GetWidth());

		auto fillStyleColor = GetFillStyle()->GetColor();
		if (fillStyleColor.has_value())
		{
			canvas.BeginFill(fillStyleColor.value());
		}

		canvas.MoveTo(m_point1.x, m_point1.y);
		canvas.LineTo(m_point2.x, m_point2.y);
		canvas.MoveTo(m_point2.x, m_point2.y);
		canvas.LineTo(m_point3.x, m_point3.y);
		canvas.MoveTo(m_point3.x, m_point3.y);
		canvas.LineTo(m_point1.x, m_point1.y);

		canvas.EndFill();
	}
private:
	Point m_point1;
	Point m_point2;
	Point m_point3;
};