#pragma once

#include "IColorStyle.h"

class ILineStyle : public IColorStyle
{
public:
	virtual unsigned GetWidth() const = 0;
	virtual void SetWidth(const unsigned width) = 0;
};