#pragma once
#include <array>
#include <cassert>

#include "Geometry.h"
#include "Color.h"

class Tile
{
public:
	// Размер тайла 8*8 пикселей.
	constexpr static int SIZE = 8;

	// Конструктор по умолчанию. Заполняет тайл указанным цветом.
	Tile(Color color = DEFAULT_COLOR) noexcept
	{
		std::array<Color, SIZE> tempArr;
		tempArr.fill(color);
		m_pixels.fill(tempArr);
		assert(m_instanceCount >= 0);
		++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
	}

	Tile(const Tile& other)
		:m_pixels(other.m_pixels)
	{
		assert(m_instanceCount >= 0);
		++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
	}

	~Tile()
	{
		--m_instanceCount; // Уменьшаем счётчик тайлов.
		assert(m_instanceCount >= 0);
	}

	/**
	 * Изменяет цвет пикселя тайла.
	 * Если координаты выходят за пределы тайла, метод ничего не делает.
	 */
	void SetPixel(const Point& p, Color color) noexcept
	{
		if (IsPointInSize(p, { SIZE, SIZE }))
		{
			m_pixels[p.y][p.x] = color;
		}
	}

	/**
	 * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
	 */
	Color GetPixel(const Point& p) const noexcept
	{
		if (IsPointInSize(p, { SIZE, SIZE }))
		{
			return m_pixels[p.y][p.x];
		}

		return DEFAULT_COLOR;
	}

	// Возвращает количество экземпляра класса Tile в программе.
	static int GetInstanceCount() noexcept
	{
		return m_instanceCount;
	}

private:
	inline static int m_instanceCount = 0;
	//использовать std::array от std::array(поправил)
	std::array<std::array<Color, SIZE>, SIZE> m_pixels;
};