#pragma once
#include <iosfwd>
#include <string>
#include <vector>

#include "Geometry.h"
#include "CoW.h"
#include "Tile.h"
#include "Color.h"

class Image
{
public:
    /**
     * ������������ ����������� ��������� �������. ���� ������� �� �������� ��������������,
     * ����������� ���������� std::out_of_range.
     */
    explicit Image(const Size& size, Color color = DEFAULT_COLOR);

    // ���������� ������ ����������� � ��������.
    Size GetSize() const noexcept;

    /**
     * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
     * �����������, ���������� �������.
     */
    uint32_t GetPixel(const Point& p) const noexcept;

    /**
     * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
     * �������� ������������.
     */
    void SetPixel(const Point& p, Color color);

private:
    Size m_size;
    std::vector<std::vector<CoW<Tile>>> m_tiles;
};

/**
 * ������� � ����� out ����������� � ���� ��������.
 */
void SaveImage(const Image& img, const std::string fileName);

/**
 * ��������� ����������� �� pixels. ����� ����������� ����������� ��������� \n.
 * ������� �������� ������������ �� ���������� ��������� ������ � ����� ������� �����.
 */
Image LoadImage(const std::string& pixels);
