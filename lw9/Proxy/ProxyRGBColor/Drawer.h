#pragma once

#include "Image.h"

/**
 * ������ ������� ������ ����� ����� ������� from � to ������ color �� ����������� Image.
 *
 * ��� ��������� ������������ �������� ����������.
 * (https://ru.wikipedia.org/wiki/��������_����������)
 */

void DrawLine(Image& image, const Point& from, const Point& to, const Color color);
void DrawCircle(Image& image, const Point& center, const int radius, const Color color);
void FillCircle(Image& image, const Point& center, const int radius, Color color);