#pragma once

#include "ILineStyle.h"

class CLineStyle : public ILineStyle
{
public:
	CLineStyle(
		unsigned width, 
		std::optional<RGBAColor> color = std::nullopt,
		std::optional<bool> isEnabled = std::nullopt
	)
		: m_width(width)
		, m_color(color)
		, m_isEnabled(isEnabled)
	{}

	unsigned GetWidth() const override
	{
		return m_width;
	}

	void SetWidth(const unsigned newWidth) override
	{
		m_width = newWidth;
	}

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
	unsigned m_width;
};