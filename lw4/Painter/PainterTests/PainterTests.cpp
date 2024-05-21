#include <sstream>
#include <iostream>
#include "../../../catch/catch.hpp"
#include "../Painter/ICanvas.h"
#include "../Painter/ShapeFactory.h"
#include "../Painter/Designer.h"
#include "../Painter/CPainter.h"

class CTestCanvas : public ICanvas
{
public:
	CTestCanvas(std::stringstream& stream)
		:m_stream(stream)
	{}

	void SetColor(Color color) override
	{
		m_color = color;
	}

	void DrawLine(Point from, Point to) override
	{
		m_stream << "line " << std::to_string(int(from.x)) << " " << std::to_string(int(from.y))
			<< " " << std::to_string(int(to.x)) << " " << std::to_string(int(to.y)) << " " << ColorToString(m_color) << std::endl;
	}

	void DrawEllipse(Point leftTop, unsigned width, unsigned height) override
	{
		m_stream << "ellipse " << std::to_string(int(leftTop.x)) << " " << std::to_string(int(leftTop.y))
			<< " " << std::to_string(width) << " " << std::to_string(height) << " " << ColorToString(m_color) << std::endl;
	}
private:
	std::stringstream& m_stream;
	Color m_color = DEFAULT_COLOR;
};

TEST_CASE("Check work with incorrect params")
{
	CShapeFactory factory;
	CDesigner designer(factory);

	std::stringstream testStream;

	testStream << "" << std::endl;
	REQUIRE_THROWS(designer.CreateDraft(testStream));
	testStream.str(std::string());

	testStream << "rectangle 10 10 20 20 purple" << std::endl;
	REQUIRE_THROWS(designer.CreateDraft(testStream));
	testStream.str(std::string());

	testStream << "circle 10 10 20 20 red" << std::endl;
	REQUIRE_THROWS(designer.CreateDraft(testStream));
	testStream.str(std::string());

	testStream << "ellipse 10 10 -1 20 red" << std::endl;
	REQUIRE_THROWS(designer.CreateDraft(testStream));
	testStream.str(std::string());

	testStream << "regularPolygon 10 10 20 -1 red" << std::endl;
	REQUIRE_THROWS(designer.CreateDraft(testStream));
	testStream.str(std::string());
}

TEST_CASE("Check factory create ellipse")
{
	CShapeFactory factory;
	std::stringstream testStream;
	std::stringstream outputStream;
	std::string checkString;

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CTestCanvas canvas(outputStream);
	CPainter painter;

	testStream << "ellipse 10 10 20 5 red" << std::endl;
	CPictureDraft draft = designer.CreateDraft(testStream);
	painter.DrawPicture(draft, canvas);
	REQUIRE(outputStream.str() == "ellipse 5 -10 10 40 #FF0000\n");
}

TEST_CASE("Check factory create triangle")
{
	CShapeFactory factory;
	std::stringstream testStream;
	std::stringstream outputStream;

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CTestCanvas canvas(outputStream);
	CPainter painter;

	testStream << "triangle 10 10 20 5 30 40 black" << std::endl;
	CPictureDraft draft = designer.CreateDraft(testStream);
	painter.DrawPicture(draft, canvas);
	REQUIRE(outputStream.str() == "line 10 10 20 5 #000000\nline 20 5 30 40 #000000\nline 30 40 10 10 #000000\n");
}

TEST_CASE("Check factory create rectangle")
{
	CShapeFactory factory;
	std::stringstream testStream;
	std::stringstream outputStream;

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CTestCanvas canvas(outputStream);
	CPainter painter;

	testStream << "rectangle 10 10 20 20 blue" << std::endl;
	CPictureDraft draft = designer.CreateDraft(testStream);
	painter.DrawPicture(draft, canvas);
	REQUIRE(outputStream.str() == "line 10 10 20 10 #0000FF\nline 20 10 20 20 #0000FF\nline 20 20 10 20 #0000FF\nline 10 20 10 10 #0000FF\n");
}

TEST_CASE("Check factory create regular polygon")
{
	CShapeFactory factory;
	std::stringstream testStream;
	std::stringstream outputStream;
	std::string checkString;

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CTestCanvas canvas(outputStream);
	CPainter painter;

	Point dot1(20, 10);
	Point dot2(10 + 10 * cos(2 * M_PI / 3), 10 + 10 * sin(2 * M_PI / 3));
	Point dot3(10 + 10 * cos(4 * M_PI / 3), 10 + 10 * sin(4 * M_PI / 3));

	std::string testStr = "line " + std::to_string(int(dot1.x)) + " " + std::to_string(int(dot1.y)) + " "
		+ std::to_string(int(dot2.x)) + " " + std::to_string(int(dot2.y)) + " #0000FF\nline "
		+ std::to_string(int(dot2.x)) + " " + std::to_string(int(dot2.y)) + " "
		+ std::to_string(int(dot3.x)) + " " + std::to_string(int(dot3.y)) + " #0000FF\nline "
		+ std::to_string(int(dot3.x)) + " " + std::to_string(int(dot3.y)) + " "
		+ std::to_string(int(dot1.x)) + " " + std::to_string(int(dot1.y)) + " #0000FF\n";

	testStream << "regularPolygon 10 10 10 3 blue" << std::endl;
	CPictureDraft draft = designer.CreateDraft(testStream);
	painter.DrawPicture(draft, canvas);
	REQUIRE(outputStream.str() == testStr);
}