#pragma once
#include <optional>
#include <fstream>
#include <sstream>
#include <format>
#include <string>

#include "ICanvas.h"
#include "CommonTypes.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(const std::string& fileName, const double width, const double height)
		:m_fileName(fileName)
		, m_point({ 0, 0 })
	{
		if (width <= 0)
		{
			throw std::out_of_range("Invalid width");
		}
		m_width = width;
		if (height <= 0)
		{
			throw std::out_of_range("Invalid width");
		}
		m_height = height;
	}

	void SetLineColor(RGBAColor color) override
	{
		m_outlineColor = color;
	}

	void SetLineWidth(unsigned width) override
	{
		m_strokeWidth = width;
	}

	void BeginFill(RGBAColor color) override
	{
		if (m_isBeginFill)
		{
			throw std::logic_error("Fill already begun");
		}
		m_isBeginFill = true;
		m_fillPos = m_svgTags.tellp();
		m_fillColor = color;
	}

	void EndFill() override
	{
		if (!m_isBeginFill)
		{
			throw std::logic_error("Fill not begun");
		}
		FillArea();
		m_isBeginFill = false;
		m_fillColor = std::nullopt;
		m_fillAreaPoints = {};
	}

	void MoveTo(double x, double y) override
	{
		m_point.x = x;
		m_point.y = y;
	}

	void LineTo(double x, double y) override
	{
		m_svgTags << std::format(R"(<line x1="{}" y1="{}" x2="{}" y2="{}"" )", m_point.x, m_point.y, x, y);
		if (m_outlineColor.has_value())
		{
			m_svgTags << format(R"( stroke={} stroke-width="{}")", ColorToString(m_outlineColor.value()), m_strokeWidth);
		}
		m_svgTags << "/>" << std::endl;

		if (m_fillColor.has_value())
		{
			m_fillAreaPoints.push_back(m_point);
			m_fillAreaPoints.push_back({ x, y });
		}
	}

	void DrawEllipse(double left, double top, double width, double height) override
	{
		Point center(left + width / 2, top + height / 2);

		m_svgTags << std::format(R"(<ellipse cx="{}" cy="{}" rx="{}" ry="{}" )", center.x, center.y, width / 2, height / 2);

		if (m_fillColor.has_value())
		{
			auto color = *m_fillColor;
			m_svgTags << format(R"( fill={})", ColorToString(color));

		}
		if (m_outlineColor.has_value())
		{
			m_svgTags << format(R"( stroke={} stroke-width="{}")", ColorToString(m_outlineColor.value()), m_strokeWidth);
		}

		m_svgTags << "/>" << std::endl;
	}

	void Save()
	{
		std::ofstream outputFile(m_fileName);

		if (!outputFile.is_open())
		{
			throw std::invalid_argument("Not founded output file");
		}

		outputFile <<std::format(R"(<svg xmlns=\"http://www.w3.org/2000/svg\" width="{}" height="{}">)", m_width, m_height) << std::endl;
		outputFile << m_svgTags.str();
		outputFile << "</svg>";
	}
private:
	std::string ColorToString(RGBAColor color)
	{
		return std::format(R"("rgb{}{}, {}, {}{}")", '(', ((color >> 16) & 255), ((color >> 8) & 255), (color & 255), ')');
	}

	void FillArea()
	{
		if (m_fillAreaPoints.empty() || !m_fillColor.has_value())
		{
			return;
		}

		auto color = m_fillColor.value();
		std::string lines = m_svgTags.str().substr(static_cast<unsigned>(m_fillPos));

		m_svgTags.seekp(m_fillPos, std::ios::beg);

		m_svgTags << std::format(R"(<path d="M {} {})", m_fillAreaPoints[0].x, m_fillAreaPoints[0].y);

		for (size_t i = 1; i < m_fillAreaPoints.size(); ++i)
		{
			m_svgTags << std::format(R"( L {} {})", m_fillAreaPoints[i].x, m_fillAreaPoints[i].y);
		}

		m_svgTags << " Z\"";
		m_svgTags << format(R"( fill={})", ColorToString(color));
		m_svgTags << "/>" << std::endl;
		m_svgTags << lines;
	}

	Point m_point;
	std::string m_fileName;
	std::stringstream m_svgTags;
	std::optional<RGBAColor> m_outlineColor;
	std::optional<RGBAColor> m_fillColor;
	unsigned m_strokeWidth = 0;
	bool m_isBeginFill = false;
	double m_width;
	double m_height;
	std::streampos m_fillPos;
	std::vector<Point> m_fillAreaPoints;
};