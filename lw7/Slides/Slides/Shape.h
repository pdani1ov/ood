#pragma once

#include "IShape.h"
#include "IGroupShape.h"
#include "LineStyle.h"
#include "ColorStyle.h"

class CShape: public IShape
{
public:
	std::shared_ptr<ILineStyle> GetOutlineStyle() override
	{
		return m_lineStyle;
	}

	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override
	{
		return m_lineStyle;
	}

	std::shared_ptr<IColorStyle> GetFillStyle() override
	{
		return m_fillStyle;
	}

	std::shared_ptr<const IColorStyle> GetFillStyle() const override
	{
		return m_fillStyle;
	}

	std::shared_ptr<IGroupShape> GetGroup() override
	{
		return nullptr;
	}

	std::shared_ptr<const IGroupShape> GetGroup() const override
	{
		return nullptr;
	}
protected:
	CShape(const std::shared_ptr<CLineStyle> lineStyle, const std::shared_ptr<CColorStyle> fillStyle)
		:m_lineStyle(lineStyle)
		,m_fillStyle(fillStyle)
	{}
private:
	std::shared_ptr<ILineStyle> m_lineStyle;
	std::shared_ptr<IColorStyle> m_fillStyle;
};