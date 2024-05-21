#pragma once
#include <memory>
#include <optional>

#include "IDrawable.h"
#include "ILineStyle.h"
#include "IColorStyle.h"

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual std::optional<RectD> GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<ILineStyle> GetOutlineStyle() = 0;
	virtual std::shared_ptr<const ILineStyle> GetOutlineStyle() const = 0;

	virtual std::shared_ptr<IColorStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IColorStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};