#include "../../../catch/catch.hpp"
#include "../adapterWithColors/shape_drawing_lib.h"
#include "../adapterWithColors/modern_graphics_lib.h"
#include "../adapterWithColors/ModernGraphicsLibAdapter.h"
#include "../adapterWithColors/ModernGraphicsLibClassAdapter.h"
#include <iostream>
#include <sstream>

const uint32_t TEST_COLOR = 123;

TEST_CASE("Check draw triangle with adapter")
{
	shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, TEST_COLOR);
	std::stringstream triangleResult;
	float r, g, b;
	r = (static_cast<float>((TEST_COLOR >> 16) & 0xff) / 255);
	g = (static_cast<float>((TEST_COLOR >> 8) & 0xff) / 255);
	b = (static_cast<float>((TEST_COLOR & 0xff)) / 255);
	triangleResult << "<draw>" << std::endl
		<< "  <line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\">" << std::endl
		<< "    <color r=\"" << r << "\" g=\"" << g << "\" b=\"" << b << "\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\">" << std::endl
		<< "    <color r=\"" << r << "\" g=\"" << g << "\" b=\"" << b << "\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\">" << std::endl
		<< "    <color r=\"" << r << "\" g=\"" << g << "\" b=\"" << b << "\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "</draw>" << std::endl;

	std::ostringstream out;

	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	CModernGraphicsLibAdapter adaptedRenderer(renderer);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	renderer.BeginDraw();
	painter.Draw(triangle);
	renderer.EndDraw();
	REQUIRE(out.str() == triangleResult.str());
}

TEST_CASE("Check draw rectangle with adapter")
{
	shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24);
	std::stringstream rectResult;
	rectResult << "<draw>" << std::endl
		<< "  <line fromX=\"30\" fromY=\"40\" toX=\"48\" toY=\"40\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"48\" fromY=\"40\" toX=\"48\" toY=\"64\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"48\" fromY=\"64\" toX=\"30\" toY=\"64\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"30\" fromY=\"64\" toX=\"30\" toY=\"40\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "</draw>" << std::endl;

	std::ostringstream out;

	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	CModernGraphicsLibAdapter adaptedRenderer(renderer);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	renderer.BeginDraw();
	painter.Draw(rectangle);
	renderer.EndDraw();
	REQUIRE(out.str() == rectResult.str());
}

TEST_CASE("Check draw triangle with class adapter")
{
	shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, TEST_COLOR);
	std::stringstream triangleResult;
	float r, g, b;
	r = (static_cast<float>((TEST_COLOR >> 16) & 0xff) / 255);
	g = (static_cast<float>((TEST_COLOR >> 8) & 0xff) / 255);
	b = (static_cast<float>((TEST_COLOR & 0xff)) / 255);
	triangleResult << "<draw>" << std::endl
		<< "  <line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\">" << std::endl
		<< "    <color r=\"" << r << "\" g=\"" << g << "\" b=\"" << b << "\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\">" << std::endl
		<< "    <color r=\"" << r << "\" g=\"" << g << "\" b=\"" << b << "\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\">" << std::endl
		<< "    <color r=\"" << r << "\" g=\"" << g << "\" b=\"" << b << "\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "</draw>" << std::endl;

	std::ostringstream out;

	CModernGraphicsLibClassAdapter adaptedRenderer(out);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	adaptedRenderer.BeginDraw();
	painter.Draw(triangle);
	adaptedRenderer.EndDraw();
	REQUIRE(out.str() == triangleResult.str());
}

TEST_CASE("Check draw rectangle with class adapter")
{
	shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24);
	std::stringstream rectResult;
	rectResult << "<draw>" << std::endl
		<< "  <line fromX=\"30\" fromY=\"40\" toX=\"48\" toY=\"40\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"48\" fromY=\"40\" toX=\"48\" toY=\"64\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"48\" fromY=\"64\" toX=\"30\" toY=\"64\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "  <line fromX=\"30\" fromY=\"64\" toX=\"30\" toY=\"40\">" << std::endl
		<< "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\"/>" << std::endl
		<< "  </line>" << std::endl
		<< "</draw>" << std::endl;
	
	std::ostringstream out;

	CModernGraphicsLibClassAdapter adaptedRenderer(out);
	shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);
	adaptedRenderer.BeginDraw();
	painter.Draw(rectangle);
	adaptedRenderer.EndDraw();
	REQUIRE(out.str() == rectResult.str());
}