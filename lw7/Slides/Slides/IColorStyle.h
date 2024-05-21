#pragma once

#include "IStyle.h"

class IColorStyle : public IStyle
{
public:
	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(const RGBAColor color) = 0;
};