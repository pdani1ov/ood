#pragma once

#include "ISlide.h"
#include "Shapes.h"
#include "Shape.h"

class CSlide : public ISlide
{
public:
	double GetWidth() const override
	{
		return m_width;
	}

	double GetHeight() const override
	{
		return m_height;
	}

	void SetWidth(unsigned width) override
	{
		m_width = width;
	}

	void SetHeight(unsigned height) override
	{
		m_height = height;
	}

	IShapes& GetShapes() override
	{
		return m_shapes;
	}

	size_t GetShapesCount() const
	{
		return m_shapes.GetShapesCount();
	}

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index)
	{
		return m_shapes.GetShapeAtIndex(index);
	}

	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max())
	{
		m_shapes.InsertShape(shape, position);
	}

	void RemoveShapeAtIndex(size_t index)
	{
		if (index >= m_shapes.GetShapesCount())
		{
			throw std::out_of_range("Invalid index");
		}
		m_shapes.RemoveShapeAtIndex(index);
	}

	RGBAColor GetBackgroundColor() const
	{
		return m_backgroundColor;
	}

	void SetBackgroundColor(RGBAColor color)
	{
		m_backgroundColor = color;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.BeginFill(m_backgroundColor);
		canvas.SetLineColor(0);
		canvas.MoveTo(0, 0);
		canvas.LineTo(m_width, 0);
		canvas.MoveTo(m_width, 0);
		canvas.LineTo(m_width, m_height);
		canvas.MoveTo(m_width, m_height);
		canvas.LineTo(0, m_height);
		canvas.MoveTo(0, m_height);
		canvas.LineTo(0, 0);
		canvas.EndFill();

		for (size_t i = 0; i < m_shapes.GetShapesCount(); i++)
		{
			auto shape = m_shapes.GetShapeAtIndex(i);
			shape->Draw(canvas);
		}
	}
private:
	double m_width = 0;
	double m_height = 0;

	CShapes m_shapes;

	RGBAColor m_backgroundColor = 0xffffff;
};