#include "../../../catch/catch.hpp"
#include "../adapter/shape_drawing_lib.h"
#include "../adapter/modern_graphics_lib.h"
#include "../adapter/ModernGraphicsLibAdapter.h"
#include "../adapter/ModernGraphicsLibClassAdapter.h"
#include <iostream>
#include <sstream>

shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
std::string triangleResult =
"<draw>\n"
"  <line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\"/>\n"
"  <line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\"/>\n"
"  <line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\"/>\n"
"</draw>\n";

shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24);
std::string rectResult =
"<draw>\n"
"  <line fromX=\"30\" fromY=\"40\" toX=\"48\" toY=\"40\"/>\n"
"  <line fromX=\"48\" fromY=\"40\" toX=\"48\" toY=\"64\"/>\n"
"  <line fromX=\"48\" fromY=\"64\" toX=\"30\" toY=\"64\"/>\n"
"  <line fromX=\"30\" fromY=\"64\" toX=\"30\" toY=\"40\"/>\n"
"</draw>\n";

TEST_CASE("Check draw triangle with adapter")
{
	std::ostringstream out;

	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	CModernGraphicsLibAdapter adaptedRenderer(renderer);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	renderer.BeginDraw();
	painter.Draw(triangle);
	renderer.EndDraw();
	REQUIRE(out.str() == triangleResult);
}

TEST_CASE("Check draw rectangle with adapter")
{
	std::ostringstream out;

	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	CModernGraphicsLibAdapter adaptedRenderer(renderer);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	renderer.BeginDraw();
	painter.Draw(rectangle);
	renderer.EndDraw();
	REQUIRE(out.str() == rectResult);
}

TEST_CASE("Check draw triangle with class adapter")
{
	std::ostringstream out;

	CModernGraphicsLibClassAdapter adaptedRenderer(out);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	adaptedRenderer.BeginDraw();
	painter.Draw(triangle);
	adaptedRenderer.EndDraw();
	REQUIRE(out.str() == triangleResult);
}

TEST_CASE("Check draw rectangle with class adapter")
{
	std::ostringstream out;

	CModernGraphicsLibClassAdapter adaptedRenderer(out);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	adaptedRenderer.BeginDraw();
	painter.Draw(rectangle);
	adaptedRenderer.EndDraw();
	REQUIRE(out.str() == rectResult);
}