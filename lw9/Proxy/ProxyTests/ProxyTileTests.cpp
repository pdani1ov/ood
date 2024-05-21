#include "../../../catch/catch.hpp"
#include "../Proxy/Tile.h"

TEST_CASE("Check init tile")
{
	Tile tile('-');
	REQUIRE(tile.GetPixel({ 0, 0 }) == '-');
	REQUIRE(tile.GetInstanceCount() == 1);
}

TEST_CASE("Check set pixel in tile")
{
	Tile tile('-');

	tile.SetPixel({ 0, 0 }, '#');
	REQUIRE(tile.GetPixel({ 0, 0 }) == '#');
	REQUIRE(tile.GetPixel({ 0, 1 }) == '-');
}

TEST_CASE("Ñheck set and get pixel at point outside size range in tile")
{
	Tile tile('-');

	REQUIRE_NOTHROW(tile.SetPixel({ Tile::SIZE, Tile::SIZE }, '#'));
	REQUIRE(tile.GetPixel({ Tile::SIZE, Tile::SIZE }) == ' ');
}

TEST_CASE("Check copy construstor and destructor in tile")
{
	Tile tile('-');
	REQUIRE(Tile::GetInstanceCount() == 1);
	{
		Tile copyTile(tile);
		REQUIRE(Tile::GetInstanceCount() == 2);
	}
	REQUIRE(Tile::GetInstanceCount() == 1);
}