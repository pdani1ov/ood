#pragma once
#include "WeatherInfo.h"
#include "Observer.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo, WeatherParameter>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo, WeatherParameter>& observable, std::set<WeatherParameter> params) override
	{
		std::cout << "Station name " << observable.GetName() << std::endl;
		if (params.contains(WeatherParameter::Temperature)) {
			std::cout << "Current Temp " << data.temperature << std::endl;
		}
		if (params.contains(WeatherParameter::Humidity)) {
			std::cout << "Current Hum " << data.humidity << std::endl;
		}
		if (params.contains(WeatherParameter::Pressure)) {
			std::cout << "Current Pressure " << data.pressure << std::endl;
		}
		if (params.contains(WeatherParameter::Wind)) {
			std::cout << "Current wind speed " << data.windSpeed << std::endl;
			std::cout << "Current wind direction " << data.windDirection << std::endl;
		}
		std::cout << "----------------" << std::endl;
	}
};