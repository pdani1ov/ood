#pragma once

#include "IGroupShape.h"
#include "CompositeColorStyle.h"
#include "CompositeLineStyle.h"
#include "Shapes.h"

class CGroupShape : public IGroupShape, public std::enable_shared_from_this<CGroupShape>
{
public:
	CGroupShape();

	size_t GetShapesCount() const override;
	void InsertShape(const std::shared_ptr<IShape>& shape, const size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) const override;
	void RemoveShapeAtIndex(const size_t index) override;

	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;
	std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;
	std::shared_ptr<IColorStyle> GetFillStyle() override;
	std::shared_ptr<const IColorStyle> GetFillStyle() const override;
	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas& canvas) const override;
private:
	void EnumerateOutlineStyle(const LineStyleCallback& callback);
	void EnumerateFillStyle(const ColorStyleCallback& callback);

	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IColorStyle> m_fillStyle;

	CShapes m_shapes;
};