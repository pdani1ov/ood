#pragma once
#include <sstream>
#include <fstream>

#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(const std::string& fileName)
		: m_fileName(fileName)
		, m_currentPoint({ 0, 0 })
		, m_currentColor("#000000")
	{}

	void SetColor(const Color& color) override
	{
		m_currentColor = color;
	}

	void MoveTo(const Point& point) override
	{
		m_currentPoint = point;
	}

	void LineTo(const Point& point) override
	{
		m_svgTags << "<line x1 = \"" << std::to_string(m_currentPoint.x) << "\""
			<< " y1=\"" << std::to_string(m_currentPoint.y) << "\" x2=\"" << std::to_string(point.x) << "\""
			<< " y2=\"" + std::to_string(point.y) << "\" stroke = \"" << m_currentColor.GetHex() << "\"/>" << std::endl;

		Save();
	}

	void DrawEllipse(const Point& center, const double rx, const double ry) override
	{
		m_svgTags << "<ellipse cx=\"" << std::to_string(center.x) << "\"" << " cy=\"" << std::to_string(center.y)
			<< "\" rx=\"" << std::to_string(rx) << "\"" << " ry=\"" << std::to_string(ry) << "\""
			<< " fill=\"white\" stroke=\"" + m_currentColor.GetHex() << "\" " << "stroke-width=\"1\"/>" << std::endl;

		Save();
	}

	void DrawText(const Point& point, const double fontSize, const std::string& text) override
	{
		m_svgTags << "<text x = \"" << std::to_string(point.x) << "\""
			<< " y = \"" << std::to_string(point.y) << "\" stroke = \"" << m_currentColor.GetHex() << "\""
			<< " font-size=\"" << std::to_string(fontSize) << "\" >" << text << "</text>" << std::endl;

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
	std::stringstream m_svgTags;
	Color m_currentColor;
	Point m_currentPoint;
};