#include "GroupShape.h"

CGroupShape::CGroupShape()
	:m_fillStyle(std::make_shared<CCompositeColorStyle>(std::bind(&CGroupShape::EnumerateFillStyle, this, std::placeholders::_1)))
	,m_outlineStyle(std::make_shared<CCompositeLineStyle>(std::bind(&CGroupShape::EnumerateOutlineStyle, this, std::placeholders::_1)))
{}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.GetShapesCount();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, const size_t position)
{
	m_shapes.InsertShape(shape, position);
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(const size_t index) const
{
	return m_shapes.GetShapeAtIndex(index);
}

void CGroupShape::RemoveShapeAtIndex(const size_t index)
{
	m_shapes.RemoveShapeAtIndex(index);
}

std::optional<RectD> CGroupShape::GetFrame() const
{
	if (m_shapes.GetShapesCount() == 0)
	{
		return std::nullopt;
	}

	double minX = std::numeric_limits<double>::max();
	double minY = std::numeric_limits<double>::max();
	double maxX = std::numeric_limits<double>::min();
	double maxY = std::numeric_limits<double>::min();

	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		std::shared_ptr<IShape> shape = m_shapes.GetShapeAtIndex(i);

		std::optional<RectD> frame = shape->GetFrame();
		
		if (!frame.has_value())
		{
			continue;
		}

		if (frame.value().left < minX)
		{
			minX = frame.value().left;
		}

		if (frame.value().top < minY)
		{
			minY = frame.value().top;
		}

		if (frame.value().left + frame.value().width > maxX)
		{
			maxX = frame.value().left + frame.value().width;
		}

		if (frame.value().top + frame.value().height > maxY)
		{
			maxY = frame.value().top + frame.value().height;
		}
	}

	RectD rect;
	rect.left = minX;
	rect.top = minY;
	rect.width = maxX - minX;
	rect.height = maxY - minY;

	return rect;
}

void CGroupShape::SetFrame(const RectD& rect)
{
	std::optional<RectD> currentFrame = GetFrame();

	if (!currentFrame.has_value())
	{
		return;
	}

	double relativeWidth = rect.width / currentFrame.value().width;
	double relativeHeight = rect.height / currentFrame.value().height;

	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		std::shared_ptr<IShape> shape = m_shapes.GetShapeAtIndex(i);

		std::optional<RectD> shapeFrame = shape->GetFrame();

		if (!shapeFrame.has_value())
		{
			continue;
		}

		double shapeLeft = (shapeFrame.value().left - currentFrame.value().left) * relativeWidth;
		double shapeTop = (shapeFrame.value().top - currentFrame.value().top) * relativeHeight;

		shape->SetFrame({
			rect.left + shapeLeft,
			rect.top + shapeTop,
			shapeFrame.value().width * relativeWidth,
			shapeFrame.value().height * relativeHeight
		});
	}
}

std::shared_ptr<ILineStyle> CGroupShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<const ILineStyle> CGroupShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IColorStyle> CGroupShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IColorStyle> CGroupShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return shared_from_this();
}

void CGroupShape::Draw(ICanvas& canvas) const
{
	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		m_shapes.GetShapeAtIndex(i)->Draw(canvas);
	}
}

void CGroupShape::EnumerateFillStyle(const ColorStyleCallback& callback)
{
	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		std::shared_ptr<IShape> shape = m_shapes.GetShapeAtIndex(i);
		callback(*shape->GetFillStyle());
	}
}

void CGroupShape::EnumerateOutlineStyle(const LineStyleCallback& callback)
{
	for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
	{
		std::shared_ptr<IShape> shape = m_shapes.GetShapeAtIndex(i);
		callback(*shape->GetOutlineStyle());
	}
}