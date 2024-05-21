#pragma once
#include <functional>

#include "IColorStyle.h"

typedef std::function<void(IColorStyle& style)> ColorStyleCallback;
typedef std::function<void(const ColorStyleCallback& callback)> ColorStyleEnumerator;

class CCompositeColorStyle : public IColorStyle
{
public:
	CCompositeColorStyle(const ColorStyleEnumerator& enumerator)
		:m_enumerator(enumerator)
	{}

	std::optional<RGBAColor> GetColor() const override
	{
		std::optional<RGBAColor> color;
		std::optional<bool> colorsIsEqual;

		auto getColorCallback = [&color, &colorsIsEqual](IColorStyle& style)
		{
			if (colorsIsEqual == std::optional<bool>{false})//colorIsEqual == std::optional<bool>{false}
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

	std::optional<bool> IsEnabled() const override
	{
		return std::nullopt;
	}

	void Enable(const bool enable) override
	{}
private:
	ColorStyleEnumerator m_enumerator;
};