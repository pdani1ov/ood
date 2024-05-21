#pragma once
#include <regex>

inline bool IsValidHexColor(std::string const& str)
{
	const std::string_view HEX_COLOR_REGEX = "^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$";
	const std::regex pattern(HEX_COLOR_REGEX.data());

	return regex_match(str, pattern);
}

class Color
{
public:

	Color(int r, int g, int b)
	{
		m_hex = RgbToHex(r, g, b);
	}

	Color(std::string hex)
	{
		if (!IsValidHexColor(hex))
		{
			throw std::invalid_argument("Invalid hex");
		}
		
		m_hex = hex;
	}

	std::string GetHex() const {
		return m_hex;
	}
private:

	std::string RgbToHex(int r, int g, int b)
	{
		std::stringstream ss;
		ss << "#" << std::hex << (r << 16 | g << 8 | b);
		return ss.str();
	}

	std::string m_hex;
};