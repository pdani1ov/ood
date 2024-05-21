#include "shape_drawing_lib.h"
#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include "ModernGraphicsLibAdapter.h"
#include "ModernGraphicsLibClassAdapter.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{

	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		CRectangle rectangle({ 30, 40 }, 18, 24);
		// TODO: нарисовать прямоугольник и треугольник при помощи painter
		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
		CModernGraphicsLibAdapter adaptedRenderer(renderer);
		shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
		renderer.BeginDraw();
		PaintPicture(painter);
		renderer.EndDraw();
	}

	void PaintPictureOnModernGraphicsRendererWithClassAdapter()
	{
		CModernGraphicsLibClassAdapter adaptedRendered(std::cout);
		shape_drawing_lib::CCanvasPainter painter(adaptedRendered);
		adaptedRendered.BeginDraw();
		PaintPicture(painter);
		adaptedRendered.EndDraw();
	}

}

int main()
{
	std::cout << "Should we use new API (y)?";
	std::string userInput;
	if (std::getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		std::cout << "Should we use class adapter (y)?";
		if (std::getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
		{
			std::cout << "class adapter" << std::endl;
			app::PaintPictureOnModernGraphicsRendererWithClassAdapter();
		}
		else
		{
			app::PaintPictureOnModernGraphicsRenderer();
		}
	}
	else
	{
		app::PaintPictureOnCanvas();
	}
	return 0;
}
