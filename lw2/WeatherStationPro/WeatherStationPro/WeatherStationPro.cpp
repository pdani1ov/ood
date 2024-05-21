#include <iostream>
#include "WeatherDataPro.h"
#include "Display.h"
#include "StatsDisplay.h"
#include "WeatherData.h"

int main()
{
	CWeatherDataPro wdPro("1");
	CWeatherData wd("2");

	CDisplay display;
	wd.RegisterObserver(display, 2);
	wdPro.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);
	wdPro.RegisterObserver(statsDisplay, 2);

	wd.SetMeasurements(3, 0.7, 760);
	wdPro.SetMeasurements(4, 0.8, 761, 270, 90);
	wd.SetMeasurements(4, 0.8, 761);
	wdPro.SetMeasurements(10, 0.5, 800, 50, 277);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);

	wdPro.SetMeasurements(-10, 0.8, 761, 90, 45);

	return 0;
}
