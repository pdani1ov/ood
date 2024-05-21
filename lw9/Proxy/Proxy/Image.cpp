#include "Image.h"

#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

/**
 * Конструирует изображение заданного размера. Если размеры не являются положительными,
 * выбрасывает исключение std::out_of_range.
 */
Image::Image(Size const& size, Color color)
{
	//не учел размеры равные нулю(поправил)
	if (size.height <= 0 || size.width <= 0)
	{
		throw std::out_of_range("Inavalid size");
	}
	m_size = size;

	//(размер + размер тайла - 1) / размер тайла(поправил)
	size_t quantityOfHorizontalTiles = (m_size.width + Tile::SIZE - 1) / Tile::SIZE;
	size_t quantityOfVerticalTiles = (m_size.height + Tile::SIZE - 1) / Tile::SIZE;

	m_tiles = std::vector<std::vector<CoW<Tile>>>(
		quantityOfVerticalTiles,
		std::vector<CoW<Tile>>(quantityOfHorizontalTiles, CoW<Tile>(color))
	);
}

// Возвращает размер изображения в пикселях.
Size Image::GetSize() const noexcept
{
	return m_size;
}

/**
 * Возвращает «цвет» пикселя в указанных координатах.Если координаты выходят за пределы
 * изображения, возвращает «пробел».
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
 * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
 * действие игнорируется.
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
 * Выводит в поток out изображение в виде символов.
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
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
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