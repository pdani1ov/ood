#pragma once
#include <functional>

#include "ILineStyle.h"

typedef std::function<void(ILineStyle& style)> LineStyleCallback;
typedef std::function<void(const LineStyleCallback& callback)> LineStyleEnumerator;

class CCompositeLineStyle : public ILineStyle
{
public:
	CCompositeLineStyle(const LineStyleEnumerator& enumerator)
		:m_enumerator(enumerator)
	{}

	std::optional<RGBAColor> GetColor() const override
	{
		std::optional<RGBAColor> color = std::nullopt;
		std::optional<bool> colorsIsEqual = std::nullopt;

		auto getColorCallback = [&color, &colorsIsEqual](IColorStyle& style)
		{
			if (colorsIsEqual.has_value() && !colorsIsEqual.value())
			{
				return;
			}

			if (!colorsIsEqual.has_value())
			{
				colorsIsEqual = true;
				color = style.GetColor();
				return;
			}

			if (color != style.GetColor())
			{
				colorsIsEqual = false;
				color = std::nullopt;
			}
		};

		m_enumerator(getColorCallback);

		return color;
	}

	void SetColor(RGBAColor newColor) override
	{
		auto setColorCallback = [newColor](IColorStyle& style)
		{
			style.SetColor(newColor);
		};

		m_enumerator(setColorCallback);
	}

	unsigned GetWidth() const override
	{
		unsigned width = 0;
		std::optional<bool> widthsIsEqual = std::nullopt;

		auto getWidthCallback = [&width, &widthsIsEqual](ILineStyle& style)
		{
			if (widthsIsEqual.has_value() && !widthsIsEqual.value())
			{
				return;
			}

			if (!widthsIsEqual.has_value())
			{
				widthsIsEqual = true;
				width = style.GetWidth();
				return;
			}

			if (width != style.GetColor())
			{
				widthsIsEqual = false;
				width = 0;
			}
		};

		m_enumerator(getWidthCallback);

		return width;
	}

	void SetWidth(unsigned newWidth) override
	{
		auto setWidthCallback = [newWidth](ILineStyle& style)
		{
			style.SetWidth(newWidth);
		};

		m_enumerator(setWidthCallback);
	}

	std::optional<bool> IsEnabled() const override
	{
		return std::nullopt;
	}

	void Enable(const bool enable) override
	{}
private:
	LineStyleEnumerator m_enumerator;
};