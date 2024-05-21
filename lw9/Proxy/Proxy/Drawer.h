#pragma once

#include "Image.h"

/**
 * Рисует отрезок прямой линии между точками from и to цветом color на изображении Image.
 *
 * Для рисования используется алгоритм Брезенхэма.
 * (https://ru.wikipedia.org/wiki/Алгоритм_Брезенхэма)
 */

void DrawLine(Image& image, const Point& from, const Point& to, const Color color);
void DrawCircle(Image& image, const Point& center, const int radius, const Color color);
void FillCircle(Image& image, const Point& center, const int radius, Color color);