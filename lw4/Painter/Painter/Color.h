#pragma once
#include <stdexcept>

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black,
};

const Color DEFAULT_COLOR = Color::Black;

std::string ColorToString(Color color)
{
	switch (color)
	{
	case Color::Black:
		return "#000000";
	case Color::Blue:
		return "#0000FF";
	case Color::Green:
		return "#00FF00";
	case Color::Pink:
		return "#FFC0CB";
	case Color::Red:
		return "#FF0000";
	case Color::Yellow:
		return "#FAFF00";
	default:
		throw std::invalid_argument("Unknown color!");
	}
}

Color StringToColor(std::string colorStr)
{
	if (colorStr == "black")
	{
		return Color::Black;
	}
	else if (colorStr == "blue")
	{
		return Color::Blue;
	}
	else if (colorStr == "green")
	{
		return Color::Green;
	}
	else if (colorStr == "pink")
	{
		return Color::Pink;
	}
	else if (colorStr == "red")
	{
		return Color::Red;
	}
	else if (colorStr == "yellow")
	{
		return Color::Yellow;
	}
	else
	{
		throw std::invalid_argument("Unknown name of color!");
	}
}
