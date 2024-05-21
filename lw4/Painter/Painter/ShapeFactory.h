#pragma once
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "IShapeFactory.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include "Triangle.h"

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory()
		:m_actionMap({
			{"rectangle", std::bind(&CShapeFactory::CreateRectangle, this, std::placeholders::_1)},
			{"triangle", std::bind(&CShapeFactory::CreateTriangle, this, std::placeholders::_1)},
			{"ellipse", std::bind(&CShapeFactory::CreateEllipse, this, std::placeholders::_1)},
			{"regularPolygon", std::bind(&CShapeFactory::CreateRegularPolygon, this, std::placeholders::_1)}
		})
	{}

	ShapePtr CreateShape(std::string const& description) override
	{
		std::stringstream ss(description);

		std::vector<std::string> params = GetParams(ss);

		if (m_actionMap.find(params[0]) == m_actionMap.end())
		{
			throw std::invalid_argument("Invalid shape name");
		}

		return m_actionMap[params[0]](params);
	}
private:
	ShapePtr CreateRectangle(std::vector<std::string>& args)
	{
		if (args.size() != 6)
		{
			throw std::invalid_argument("Incorrect quantity of rectangle args!");
		}

		Point point1 = StringToPoint(args[1], args[2]);
		Point point2 = StringToPoint(args[3], args[4]);
		Color color = StringToColor(args[5]);

		return std::make_unique<CRectangle>(point1, point2, color);
	}

	ShapePtr CreateTriangle(std::vector<std::string>& args)
	{
		if (args.size() != 8)
		{
			throw std::invalid_argument("Incorrect quantity of triangle args!");
		}

		Point point1 = StringToPoint(args[1], args[2]);
		Point point2 = StringToPoint(args[3], args[4]);
		Point point3 = StringToPoint(args[5], args[6]);
		Color color = StringToColor(args[7]);

		return std::make_unique<CTriangle>(point1, point2, point3, color);
	}

	ShapePtr CreateEllipse(std::vector<std::string>& args)
	{
		if (args.size() != 6)
		{
			throw std::invalid_argument("Incorrect quantity of ellipse args!");
		}

		Point center = StringToPoint(args[1], args[2]);
		int verticalRadius = std::stoi(args[3]);
		if (verticalRadius < 0)
		{
			throw std::invalid_argument("Incorrect arg");
		}

		int horizontalRadius = std::stoi(args[4]);
		if (horizontalRadius < 0)
		{
			throw std::invalid_argument("Incorrect arg");
		}

		Color color = StringToColor(args[5]);

		return std::make_unique<CEllipse>(center, verticalRadius, horizontalRadius, color);
	}

	ShapePtr CreateRegularPolygon(std::vector<std::string>& args)
	{
		if (args.size() != 6)
		{
			throw std::invalid_argument("Incorrect quantity of regular polygon args!");
		}

		Point center = StringToPoint(args[1], args[2]);

		int radius = std::stoul(args[3]);
		if (radius < 0)
		{
			throw std::invalid_argument("Incorrect arg");
		}

		int vertexCount = std::stoul(args[4]);
		if (vertexCount < 0)
		{
			throw std::invalid_argument("Incorrect arg");
		}

		Color color = StringToColor(args[5]);

		return std::make_unique<CRegularPolygon>(center, radius, vertexCount, color);
	}

	std::vector<std::string> GetParams(std::istream& input)
	{
		std::vector<std::string> params;
		std::string param;

		while (!input.eof())
		{
			input >> param;
			params.push_back(param);
		}

		return params;
	}

	std::map<std::string, std::function<ShapePtr(std::vector<std::string>& args)>> m_actionMap;
};