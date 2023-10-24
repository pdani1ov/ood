#pragma once

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windDirection = 0;
	double windSpeed = 0;
};

enum class WeatherParameter
{
	Temperature,
	Pressure,
	Humidity,
	Wind
};