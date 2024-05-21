#include "PictureController.h"

CPictureController::CPictureController(const std::string& fileName)
	:m_picture(std::make_shared<CPicture>(std::make_shared<CCanvas>(fileName)))
{
	auto exit = [this](std::istream&) { Exit(); };
	auto help = [this](std::istream&) { m_menu.ShowInstructions(); };
	auto addShape = [this](std::istream& in) { AddShape(in); };
	auto moveShape = [this](std::istream& in) { MoveShape(in); };
	auto movePicture = [this](std::istream& in) { MovePicture(in); };
	auto deleteShape = [this](std::istream& in) { DeleteShape(in); };
	auto list = [this](std::istream&) { ShowList(); };
	auto changeColor = [this](std::istream& in) { ChangeColor(in); };
	auto changeShape = [this](std::istream& in) { ChangeShape(in); };
	auto drawShape = [this](std::istream& in) { DrawShape(in); };
	auto drawPicture = [this](std::istream& in) { DrawPicture(in); };

	m_menu.AddItem("help", "Help", help);
	m_menu.AddItem("exit", "Exit", exit);
	m_menu.AddItem("AddShape", "AddShape <id> <color> <type> <params>", addShape);
	m_menu.AddItem("MoveShape", "MoveShape <id> <dx> <dy>", moveShape);
	m_menu.AddItem("MovePicture", "MovePicture <dx> <dy>", movePicture);
	m_menu.AddItem("DeleteShape", "DeleteShape <id>", deleteShape);
	m_menu.AddItem("List", "List", list);
	m_menu.AddItem("ChangeColor", "ChangeColor <id> <color>", changeColor);
	m_menu.AddItem("ChangeShape", "ChangeShape <id> <type> <params>", changeShape);
	m_menu.AddItem("DrawShape", "DrawShape <id>", drawShape);
	m_menu.AddItem("DrawPicture", "DrawPicture", drawPicture);
}

void CPictureController::Run()
{
	m_menu.Run();
}

void CPictureController::Exit()
{
	m_menu.Exit();
}

void CPictureController::AddShape(std::istream& in)
{
	std::string id, color, type;

	in >> id >> color >> type;

	if (id.empty() || !IsValidHexColor(color) || type.empty())
	{
		std::cout << "invalid command arguments, template: <id> <hex color> <shape type> <shape args>" << std::endl;
		return;
	}

	try
	{

		m_picture->AddShape(
			id,
			std::make_unique<CShape>(CreateStrategy(in, type), color)
		);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CPictureController::MoveShape(std::istream& in)
{
	std::string id, dxStr, dyStr;

	in >> id >> dxStr >> dyStr;

	if (id.empty() || dxStr.empty() || dyStr.empty())
	{
		std::cout << "Invalid command arguments, template: <id> <delta x> <delta y>" << std::endl;
		return;
	}

	try
	{
		double dx = stod(dxStr);
		double dy = stod(dyStr);
		m_picture->GetShape(id)->Move({ dx, dy });
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CPictureController::MovePicture(std::istream& in)
{
	std::string dxStr, dyStr;

	in >> dxStr >> dyStr;

	if (dxStr.empty() || dyStr.empty())
	{
		std::cout << "invalid command arguments, template: <delta x> <delta y>" << std::endl;
		return;
	}

	try
	{
		double dx = stod(dxStr);
		double dy = stod(dyStr);
		m_picture->MovePicture({ dx, dy });
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}

void CPictureController::DeleteShape(std::istream& in)
{
	std::string id;

	in >> id;

	if (id.empty())
	{
		std::cout << "invalid command arguments, template: <id>" << std::endl;
		return;
	}

	m_picture->DeleteShape(id);
}

void CPictureController::ShowList()
{
	m_picture->ShowList(std::cout);
}

void CPictureController::ChangeColor(std::istream& in)
{
	std::string id, color;

	in >> id >> color;

	if (id.empty() || !IsValidHexColor(color))
	{
		std::cout <<"Invalid command arguments, template: <id> <hex color>" << std::endl;
		return;
	}

	try
	{
		m_picture->GetShape(id)->SetColor(color);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CPictureController::ChangeShape(std::istream& in)
{
	std::string id, type;

	in >> id >> type;

	if (id.empty() || type.empty())
	{
		std::cout << "Invalid command arguments, template: <id> <shape type> <shape args>" << std::endl;
		return;
	}

	try
	{
		m_picture->GetShape(id)->SetShapeStrategy(CreateStrategy(in, type));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CPictureController::DrawShape(std::istream& in)
{
	std::string id;

	in >> id;

	if (id.empty())
	{
		std::cout << "Invalid command arguments, template: <id>" << std::endl;
		return;
	}

	try
	{
		m_picture->DrawShape(id);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CPictureController::DrawPicture(std::istream& in)
{
	m_picture->DrawPicture();
}

std::unique_ptr<IShapeStrategy> CPictureController::CreateStrategy(std::istream& in, std::string& type)
{
	if (type == "circle")
	{
		return std::make_unique<CCircleStrategy>(CreateCircleStrategy(in));
	}
	else if (type == "line")
	{
		return std::make_unique<CLineStrategy>(CreateLineStrategy(in));
	}
	else if (type == "rectangle")
	{
		return std::make_unique<CRectangleStrategy>(CreateRectangleStrategy(in));
	}
	else if (type == "text")
	{
		return std::make_unique<CTextStrategy>(CreateTextStrategy(in));
	}
	else if (type == "triangle")
	{
		return std::make_unique<CTriangleStrategy>(CreateTriangleStrategy(in));
	}
	else
	{
		throw std::invalid_argument("Unkonown shape type");
	}
}

CCircleStrategy CPictureController::CreateCircleStrategy(std::istream& in)
{
	std::string cxStr, cyStr, rStr;

	in >> cxStr >> cyStr >> rStr;

	if (cxStr.empty() || cyStr.empty() || rStr.empty())
	{
		throw std::invalid_argument("invalid circle arguments, template: <center x> <center y> <radius>");
	}

	try
	{
		double cx = stod(cxStr);
		double cy = stod(cyStr);
		double r = stod(rStr);

		return CCircleStrategy({ cx, cy }, r);
	}
	catch (...)
	{
		throw std::invalid_argument("invalid circle arguments, template: <center x> <center y> <radius>");
	}
}

CLineStrategy CPictureController::CreateLineStrategy(std::istream& in)
{
	std::string startXStr, startYStr, endXStr, endYStr;

	in >> startXStr >> startYStr >> endXStr >> endYStr;

	if (startXStr.empty() || startYStr.empty() || endXStr.empty() || endYStr.empty())
	{
		throw std::invalid_argument("invalid line arguments, template: <x1> <y1> <x2> <y2>");
	}

	try
	{
		double x1 = stod(startXStr);
		double y1 = stod(startYStr);
		double x2 = stod(endXStr);
		double y2 = stod(endYStr);

		return CLineStrategy({ x1, y1 }, { x2, y2 });
	}
	catch (...)
	{
		throw std::invalid_argument("invalid line arguments, template: <x1> <y1> <x2> <y2>");
	}
}

CRectangleStrategy CPictureController::CreateRectangleStrategy(std::istream& in)
{
	std::string leftStr, topStr, widthStr, heightStr;

	in >> leftStr >> topStr >> widthStr >> heightStr;

	if (leftStr.empty() || topStr.empty() || widthStr.empty() || heightStr.empty())
	{
		throw std::invalid_argument("invalid rectangle arguments, template: <left> <top> <width> <height>");
	}

	try
	{
		double left = stod(leftStr);
		double top = stod(topStr);
		double width = stod(widthStr);
		double height = stod(heightStr);

		return CRectangleStrategy({ left, top }, width, height);
	}
	catch (...)
	{
		throw std::invalid_argument("invalid rectangle arguments, template: <left> <top> <width> <height>");
	}
}

CTextStrategy CPictureController::CreateTextStrategy(std::istream& in)
{
	std::string xStr, yStr, fontSizeStr, text;

	in >> xStr >> yStr >> fontSizeStr;

	getline(in, text);

	if (xStr.empty() || yStr.empty() || fontSizeStr.empty() || text.empty())
	{
		throw std::invalid_argument("invalid text arguments, template: <left> <top> <size> <text>");
	}

	try
	{
		double x = stod(xStr);
		double y = stod(yStr);
		double fontSize = stod(fontSizeStr);

		return CTextStrategy({ x, y }, fontSize, text);
	}
	catch (...)
	{
		throw std::invalid_argument("invalid text arguments, template: <left> <top> <size> <text>");
	}
}

CTriangleStrategy CPictureController::CreateTriangleStrategy(std::istream& in)
{
	std::string x1Str, y1Str, x2Str, y2Str, x3Str, y3Str;

	in >> x1Str >> y1Str >> x2Str >> y2Str >> x3Str >> y3Str;

	if (x1Str.empty() || y1Str.empty() || x2Str.empty() || y2Str.empty() || x3Str.empty() || y3Str.empty())
	{
		throw std::invalid_argument("invalid triangle arguments, template: <x1> <y1> <x2> <y2> <x3> <y3>");
	}

	try
	{
		double x1 = stod(x1Str);
		double y1 = stod(y1Str);
		double x2 = stod(x2Str);
		double y2 = stod(y2Str);
		double x3 = stod(x3Str);
		double y3 = stod(y3Str);

		return CTriangleStrategy(
			{ x1, y1 },
			{ x2, y2 },
			{ x3, y3 }
		);
	}
	catch (...)
	{
		throw std::invalid_argument("invalid triangle arguments, template: <x1> <y1> <x2> <y2> <x3> <y3>");
	}
}