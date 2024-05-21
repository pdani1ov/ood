#pragma once
#include "WeatherInfo.h"
#include "Observer.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		if (data.windParams) {
			std::cout << "Current wind speed " << data.windParams.value().windSpeed << std::endl;
			std::cout << "Current wind direction " << data.windParams.value().windDirection << std::endl;
		}
		std::cout << "Station name " << observable.GetName() << std::endl;
		std::cout << "----------------" << std::endl;
	}
};