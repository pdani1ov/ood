#pragma once
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include "History.h"
#include "./IImage.h"
#include "ResizeImageCommand.h"

class CImage : public IImage
{
public:
	CImage(const std::filesystem::path& path, int width, int height, CHistory& history)
		: m_path(path), 
		m_width(width), 
		m_height(height),
		m_history(history)
	{}

	const std::filesystem::path GetPath()const override
	{
		return m_path;
	}

	int GetWidth()const override
	{
		return m_width;
	}

	int GetHeight()const override
	{
		return m_height;
	}

	void Resize(int width, int height) override
	{
		if (width < 1 || width > 10000)
		{
			throw std::invalid_argument("Incorrect width of image");
		}

		if (height < 1 || height > 10000)
		{
			throw std::invalid_argument("Incorrect height of image");
		}

		m_history.AddAndExecuteCommand(std::make_shared<CResizeImageCommand>(m_height, m_width, height, width));
	}

private:
	std::filesystem::path m_path;
	CHistory& m_history;
	int m_width;
	int m_height;

};