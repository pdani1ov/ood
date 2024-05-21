#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "ICanvas.h"
#include "Color.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::string const& filename)
		:m_fileName(filename)
	{}

	void SetColor(Color color) override
	{
		m_color = color;
	}

	void DrawLine(Point from, Point to) override
	{
		m_svgTags << "<line x1=\"" << std::to_string(from.x) << "\" y1=\"" << std::to_string(from.y) 
			<< "\" x2=\"" << std::to_string(to.x) << "\" y2=\"" << std::to_string(to.y) << "\" stroke = \"" << ColorToString(m_color) << "\"/>" << std::endl;

		Save();
	}

	void DrawEllipse(Point leftTop, unsigned width, unsigned height) override
	{


		Point center(leftTop.x + width / 2, leftTop.y + height / 2);
		m_svgTags << "<ellipse cx=\"" << std::to_string(center.x) << "\"" << " cy=\"" << std::to_string(center.y)
			<< "\" rx=\"" << std::to_string(width / 2) << "\"" << " ry=\"" << std::to_string(height / 2) << "\""
			<< " fill=\"white\" stroke=\"" + ColorToString(m_color) << "\" " << "stroke-width=\"1\"/>" << std::endl;

		Save();
	}

private:
	void Save()
	{
		std::ofstream outputFile(m_fileName);

		if (!outputFile.is_open())
		{
			throw std::invalid_argument("Not founded output file");
		}

		outputFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;
		outputFile << m_svgTags.str();
		outputFile << "</svg>";
	}

	std::string m_fileName;
	Color m_color = DEFAULT_COLOR;
	std::stringstream m_svgTags;
};