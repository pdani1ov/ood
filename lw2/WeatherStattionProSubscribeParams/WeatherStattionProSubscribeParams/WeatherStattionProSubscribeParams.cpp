#include <iostream>
#include "WeatherDataPro.h"
#include "Display.h"
#include "StatsDisplay.h"

int main()
{
	CWeatherDataPro wdPro("1");

	CDisplay display1;
	wdPro.RegisterObserver(display1, {WeatherParameter::Humidity}, 1);
	CDisplay display2;
	wdPro.RegisterObserver(display2, {WeatherParameter::Pressure, WeatherParameter::Temperature}, 0);

	wdPro.SetMeasurements(10, 10, 10, 10, 10);
	wdPro.RemoveObserver(display2, {WeatherParameter::Temperature});
	wdPro.SetMeasurements(20, 20, 20 , 20, 20);

	return 0;
}
