#pragma once

#include "IColorStyle.h"

class CColorStyle: public IColorStyle
{
public:
	CColorStyle(std::optional<RGBAColor> color = std::nullopt, std::optional<bool> isEnabled = std::nullopt)
		:m_color(color)
		,m_isEnabled(isEnabled)
	{}

	std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}

	void SetColor(RGBAColor newColor) override
	{
		m_color = newColor;
	}

	std::optional<bool> IsEnabled() const override
	{
		return m_isEnabled;
	}

	void Enable(const bool enable) override
	{
		m_isEnabled = enable;
	}
private:
	std::optional<RGBAColor> m_color;
	std::optional<bool> m_isEnabled;
};