#include "../../../catch/catch.hpp"
#include "../Slides/GroupShape.h"
#include "../Slides/Rectangle.h"
#include "../Slides/Ellipse.h"
#include "../Slides/Triangle.h"

struct CMockCanvas : ICanvas
{
	void SetLineWidth(unsigned width) override
	{
		lineWidth = width;
	}

	void SetLineColor(RGBAColor color) override 
	{
		lineColor = color;
	};
	void BeginFill(RGBAColor color) override 
	{
		fillColor = color;
	};
	void EndFill() override {};
	void MoveTo(double x, double y) override {};

	void DrawEllipse(double left, double top, double width, double height) override
	{
		countOfEllipse++;
	}

	void LineTo(double x, double y) override
	{
		countOfLines++;
	}

	void Reset()
	{
		countOfLines = 0;
		countOfEllipse = 0;
		fillColor = std::nullopt;
		lineColor = std::nullopt;
		lineWidth = 0;
	}

	size_t countOfLines = 0;
	size_t countOfEllipse = 0;
	std::optional<RGBAColor> fillColor;
	std::optional<RGBAColor> lineColor;
	unsigned lineWidth = 0;
};

TEST_CASE("Init group shape")
{
	CGroupShape shapes;

	REQUIRE(shapes.GetFrame() == std::nullopt);

	REQUIRE(!shapes.GetFillStyle()->GetColor().has_value());
	REQUIRE(!shapes.GetFillStyle()->IsEnabled().has_value());

	REQUIRE(!shapes.GetOutlineStyle()->GetColor().has_value());
	REQUIRE(shapes.GetOutlineStyle()->GetWidth() == 0);
	REQUIRE(!shapes.GetOutlineStyle()->IsEnabled().has_value());

	REQUIRE(shapes.GetShapesCount() == 0);

	REQUIRE_THROWS(shapes.GetShapeAtIndex(1));
	REQUIRE_THROWS(shapes.RemoveShapeAtIndex(1));

	REQUIRE_NOTHROW(shapes.SetFrame({ 1, 1, 1, 1 }));
	REQUIRE(shapes.GetFrame() == std::nullopt);
}

TEST_CASE("Group shape with figures")
{
	CGroupShape shapes;
	CMockCanvas canvas;

	shapes.InsertShape(std::make_shared<CRectangle>(RectD(100, 100, 150, 150), std::make_shared<CLineStyle>(5, 0x76df45), std::make_shared<CColorStyle>(0x000000)));

	REQUIRE(shapes.GetFillStyle()->GetColor() == 0x000000);
	REQUIRE(shapes.GetOutlineStyle()->GetColor() == 0x76df45);
	REQUIRE(shapes.GetOutlineStyle()->GetWidth() == 5);

	REQUIRE(shapes.GetFrame() == RectD(100, 100, 150, 150));

	REQUIRE(shapes.GetShapesCount() == 1);
	REQUIRE_NOTHROW(shapes.GetShapeAtIndex(0));
	REQUIRE(shapes.GetShapeAtIndex(0)->GetFrame() == RectD(100, 100, 150, 150));
	shapes.Draw(canvas);
	REQUIRE(canvas.countOfEllipse == 0);
	REQUIRE(canvas.countOfLines == 4);
	REQUIRE(canvas.fillColor.value() == 0x000000);
	REQUIRE(canvas.lineColor.value() == 0x76df45);
	REQUIRE(canvas.lineWidth == 5);
	canvas.Reset();

	shapes.InsertShape(std::make_shared<CEllipse>(RectD(200, 200, 200, 200), std::make_shared<CLineStyle>(1, 0x4576df), std::make_shared<CColorStyle>(0x76df45)));
	REQUIRE(!shapes.GetFillStyle()->GetColor().has_value());
	REQUIRE(!shapes.GetOutlineStyle()->GetColor().has_value());
	REQUIRE(shapes.GetOutlineStyle()->GetWidth() == 0);

	REQUIRE_NOTHROW(shapes.GetShapeAtIndex(1));
	REQUIRE(shapes.GetShapeAtIndex(1)->GetFrame() == RectD(200, 200, 200, 200));

	REQUIRE(shapes.GetFrame() == RectD(100, 100, 300, 300));

	REQUIRE(shapes.GetShapesCount() == 2);

	REQUIRE_NOTHROW(shapes.SetFrame({200, 200, 700, 700}));
	REQUIRE(shapes.GetFrame() == RectD(200, 200, 700, 700));
	REQUIRE(shapes.GetShapeAtIndex(0)->GetFrame() != RectD(100, 100, 150, 150));
	REQUIRE(shapes.GetShapeAtIndex(1)->GetFrame() != RectD(200, 200, 200, 200));

	shapes.Draw(canvas);
	REQUIRE(canvas.countOfEllipse == 1);
	REQUIRE(canvas.countOfLines == 4);
}