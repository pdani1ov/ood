#pragma once

struct Point
{
	Point(double newX, double newY)
		:x(newX),
		y(newY)
	{}

	double x;
	double y;
};

Point StringToPoint(std::string xStr, std::string yStr)
{
	double x = std::stod(xStr);
	double y = std::stod(yStr);

	return Point(x, y);
}