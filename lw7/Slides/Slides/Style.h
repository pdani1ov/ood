#pragma once
#include <optional>

#include "IStyle.h"

class CStyle : public IStyle
{
public:
	CStyle(std::optional<bool> isEnabled = std::nullopt)
		:m_isEnabled(isEnabled)
	{}

	std::optional<bool> IsEnabled() const override
	{
		return m_isEnabled;
	}

	void Enable(bool enable) override
	{
		m_isEnabled = enable;
	}
private:
	std::optional<bool> m_isEnabled;
};