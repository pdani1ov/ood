#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "Slide.h"
#include "GroupShape.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "Canvas.h"
#include "ColorStyle.h"

std::shared_ptr<ISlide> CreateSlide()
{
	auto slide = std::make_shared<CSlide>();
	auto& shapes = slide->GetShapes();

	auto group = std::make_shared<CGroupShape>();
	slide->SetBackgroundColor(0xdf7645);
	slide->SetHeight(700);
	slide->SetWidth(1300);

	group->InsertShape(std::make_shared<CRectangle>(RectD(100, 100, 150, 150), std::make_shared<CLineStyle>(5, 0x76df45), std::make_shared<CColorStyle>(0x000000)));
	group->InsertShape(std::make_shared<CTriangle>(RectD(200, 200, 200, 200), std::make_shared<CLineStyle>(1, 0x4576df), std::make_shared<CColorStyle>(0x76df45)));
	group->InsertShape(std::make_shared<CEllipse>(RectD(500, 500, 200, 200), std::make_shared<CLineStyle>(2, 0x76df45), std::make_shared<CColorStyle>(0x4576df)));

	shapes.InsertShape(group);

	return slide;
}

void SaveSlideToFile(const std::shared_ptr<ISlide>& slide, const std::string& fileName)
{
	CCanvas canvas(fileName, slide->GetWidth(), slide->GetHeight());

	slide->Draw(canvas);

	canvas.Save();
}

int main()
{
	auto slide = CreateSlide();
	SaveSlideToFile(slide, "slide.html");

	auto& shapes = slide->GetShapes();
	auto group = shapes.GetShapeAtIndex(0);
	group->SetFrame({ 0, 0, 220, 220 });

	SaveSlideToFile(slide, "updated_slide.html"); 

	return 0;
}
