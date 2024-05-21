#pragma once
#include "WeatherInfo.h"
#include "Observer.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		if (data.windDirection && data.windSpeed) {
			std::cout << "Current wind speed " << data.windSpeed.value() << std::endl;
			std::cout << "Current wind direction " << data.windDirection.value() << std::endl;
		}
		std::cout << "Station name " << observable.GetName() << std::endl;
		std::cout << "----------------" << std::endl;
	}
};