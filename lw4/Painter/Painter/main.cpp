#include <iostream>
#include "ShapeFactory.h"
#include "Designer.h"
#include "CCanvas.h"
#include "CPainter.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Incorrect quantity of args" << std::endl;
		return 1;
	}

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];

	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Input file is not founded" << std::endl;
		return 1;
	}

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CPictureDraft draft = designer.CreateDraft(inputFile);
	CCanvas canvas(outputFileName);
	CPainter painter;

	painter.DrawPicture(draft, canvas);

	return 0;
}
