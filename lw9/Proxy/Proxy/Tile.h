#pragma once
#include <array>
#include <cassert>

#include "Geometry.h"
#include "Color.h"

class Tile
{
public:
	// ������ ����� 8*8 ��������.
	constexpr static int SIZE = 8;

	// ����������� �� ���������. ��������� ���� ��������� ������.
	Tile(Color color = DEFAULT_COLOR) noexcept
	{
		std::array<Color, SIZE> tempArr;
		tempArr.fill(color);
		m_pixels.fill(tempArr);
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
	}

	Tile(const Tile& other)
		:m_pixels(other.m_pixels)
	{
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
	}

	~Tile()
	{
		--m_instanceCount; // ��������� ������� ������.
		assert(m_instanceCount >= 0);
	}

	/**
	 * �������� ���� ������� �����.
	 * ���� ���������� ������� �� ������� �����, ����� ������ �� ������.
	 */
	void SetPixel(const Point& p, Color color) noexcept
	{
		if (IsPointInSize(p, { SIZE, SIZE }))
		{
			m_pixels[p.y][p.x] = color;
		}
	}

	/**
	 * ���������� ���� �������. ���� ���������� ������� �� ������� �����, ������������ ������.
	 */
	Color GetPixel(const Point& p) const noexcept
	{
		if (IsPointInSize(p, { SIZE, SIZE }))
		{
			return m_pixels[p.y][p.x];
		}

		return DEFAULT_COLOR;
	}

	// ���������� ���������� ���������� ������ Tile � ���������.
	static int GetInstanceCount() noexcept
	{
		return m_instanceCount;
	}

private:
	inline static int m_instanceCount = 0;
	//������������ std::array �� std::array(��������)
	std::array<std::array<Color, SIZE>, SIZE> m_pixels;
};