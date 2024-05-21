#include "../../../catch/catch.hpp"
#include "../Proxy/Image.h"

//Лучше один маленький тест, чем один большой ЛИБО сценарий с секциями(поправил)
TEST_CASE("Check init of image")
{
	Image img({ 100, 45 }, '-');

	REQUIRE(img.GetSize().height == 45);
	REQUIRE(img.GetSize().width == 100);

	REQUIRE(img.GetPixel({ 0, 0 }) == '-');
	REQUIRE(Tile::GetInstanceCount() == 1);
}

TEST_CASE("Check set pixel in image")
{
	Image img({ 100, 45 }, '-');

	img.SetPixel({ 0, 0 }, '#');
	REQUIRE(img.GetPixel({ 0, 0 }) == '#');
	REQUIRE(Tile::GetInstanceCount() == 2);

	img.SetPixel({ Tile::SIZE - 1, 0 }, '#');
	REQUIRE(img.GetPixel({ Tile::SIZE - 1, 0 }) == '#');
	REQUIRE(Tile::GetInstanceCount() == 2);
}

TEST_CASE("Сheck set and get pixel at point outside size range in image")
{
	Image img({ 100, 45 }, '-');

	REQUIRE_NOTHROW(img.SetPixel({100, 45}, '#'));
	REQUIRE(img.GetPixel({100, 45}) == ' ');
}