#pragma once
#include <optional>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::optional<WindInfo> windParams;
};

struct WindInfo
{
	double windDirection;
	double windSpeed;
};