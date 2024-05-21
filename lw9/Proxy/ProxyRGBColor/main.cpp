#include <iostream>

#include "Image.h"
#include "Drawer.h"

const Color BLACK_COLOR = 0x000000;
const Color RED_COLOR = 0xf54242;

int main()
{
	Image img({ 1000, 1000 }, DEFAULT_COLOR);
	DrawCircle(img, { 150, 150 }, 150, BLACK_COLOR);
	FillCircle(img, { 500, 500}, 150, RED_COLOR);
	SaveImage(img, "image.ppm");
}
