#pragma once
#include <optional>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;	
	std::optional<double> windDirection = std::nullopt;
	std::optional<double> windSpeed = std::nullopt;
};