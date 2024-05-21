#include "Image.h"

#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

/**
 * ������������ ����������� ��������� �������. ���� ������� �� �������� ��������������,
 * ����������� ���������� std::out_of_range.
 */
Image::Image(Size const& size, Color color)
{
	//�� ���� ������� ������ ����(��������)
	if (size.height <= 0 || size.width <= 0)
	{
		throw std::out_of_range("Inavalid size");
	}
	m_size = size;

	//(������ + ������ ����� - 1) / ������ �����(��������)
	size_t quantityOfHorizontalTiles = (m_size.width + Tile::SIZE - 1) / Tile::SIZE;
	size_t quantityOfVerticalTiles = (m_size.height + Tile::SIZE - 1) / Tile::SIZE;

	m_tiles = std::vector<std::vector<CoW<Tile>>>(
		quantityOfVerticalTiles,
		std::vector<CoW<Tile>>(quantityOfHorizontalTiles, CoW<Tile>(color))
	);
}

// ���������� ������ ����������� � ��������.
Size Image::GetSize() const noexcept
{
	return m_size;
}

/**
 * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
 * �����������, ���������� �������.
 */
Color Image::GetPixel(const Point& p) const noexcept
{
	if (IsPointInSize(p, m_size))
	{
		int tileX = p.x / Tile::SIZE;
		int tileY = p.y / Tile::SIZE;

		auto tile = m_tiles[tileY][tileX];

		return tile->GetPixel({ p.x % Tile::SIZE, p.y % Tile::SIZE });
	}

	return DEFAULT_COLOR;
}

/**
 * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
 * �������� ������������.
 */
void Image::SetPixel(const Point& p, Color color)
{
	if (IsPointInSize(p, m_size))
	{
		int tileX = p.x / Tile::SIZE;
		int tileY = p.y / Tile::SIZE;

		auto& tile = m_tiles[tileY][tileX];

		tile.Write()->SetPixel({ p.x % Tile::SIZE, p.y % Tile::SIZE }, color);
	}
}

/**
 * ������� � ����� out ����������� � ���� ��������.
 */
void Print(const Image& img, std::ostream& out)
{
	const auto size = img.GetSize();
	for (int y = 0; y < size.height; ++y)
	{
		for (int x = 0; x < size.width; ++x)
		{
			out.put(img.GetPixel({ x, y }));
		}
		out.put('\n');
	}
}

/**
 * ��������� ����������� �� pixels. ����� ����������� ����������� ��������� \n.
 * ������� �������� ������������ �� ���������� ��������� ������ � ����� ������� �����.
 */
Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (Color ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}