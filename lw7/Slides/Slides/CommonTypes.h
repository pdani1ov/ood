#pragma once
#include <cstdint>

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

typedef Rect<double> RectD;
typedef uint32_t RGBAColor;

struct Point
{
	double x = 0;
	double y = 0;
};

inline bool operator==(RectD const& rect1, RectD const& rect2)
{
	return rect1.left == rect2.left
		&& rect1.top == rect2.top
		&& rect1.width == rect2.width
		&& rect1.height == rect2.height;
}