#pragma once
#include <stdexcept>

#include "Shape.h"
#include "CommonTypes.h"

class CEllipse : public CShape
{
public:
	CEllipse(
		const Point& center, 
		const double radiusX, 
		const double radiusY,
		const std::shared_ptr<CLineStyle> lineStyle,
		const std::shared_ptr<CColorStyle> colorStyle
	)
		:CShape(lineStyle, colorStyle)
		,m_center(center)
	{
		if (radiusX <= 0)
		{
			throw std::out_of_range("Inavalid radius x");
		}
		m_radiusX = radiusX;
		
		if (radiusY <= 0)
		{
			throw std::out_of_range("Inavalid radius y");
		}
		m_radiusX = radiusY;
	}

	CEllipse(
		const RectD& rect, 
		const std::shared_ptr<CLineStyle> lineStyle,
		const std::shared_ptr<CColorStyle> colorStyle
	)
		:CShape(lineStyle, colorStyle)
		,m_center({rect.left + rect.width * 0.5, rect.top + rect.height * 0.5})
	{
		if (rect.width <= 0)
		{
			throw std::out_of_range("Inavalid width in rect");
		}
		m_radiusX = rect.width * 0.5;

		if (rect.height <= 0)
		{
			throw std::out_of_range("Inavalid height in rect");
		}
		m_radiusY = rect.height * 0.5;
	}

	std::optional<RectD> GetFrame() const override
	{
		RectD rect;
		rect.left = m_center.x - m_radiusX;
		rect.top = m_center.y - m_radiusY;
		rect.width = 2 * m_radiusX;
		rect.height = 2 * m_radiusY;

		return rect;
	}

	void SetFrame(const RectD& rect) override
	{
		m_center.x = rect.left + rect.width * 0.5;
		m_center.y = rect.top + rect.height * 0.5;

		if (rect.width <= 0)
		{
			throw std::out_of_range("Inavalid rect width");
		}
		m_radiusX = rect.width / 2;

		if (rect.height <= 0)
		{
			throw std::out_of_range("Inavalid rect height");
		}
		m_radiusY = rect.height / 2;
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

		canvas.DrawEllipse(
			m_center.x - m_radiusX,
			m_center.y - m_radiusY,
			2 * m_radiusX,
			2 * m_radiusY
		);

		canvas.EndFill();
	}
private:
	Point m_center;
	double m_radiusX = 0;
	double m_radiusY = 0;
};