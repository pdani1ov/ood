#pragma once
#include <optional>

#include "CommonTypes.h"

class IStyle
{
public:
	virtual std::optional<bool> IsEnabled() const = 0;
	virtual void Enable(bool enable) = 0;

	virtual ~IStyle() = default;
};