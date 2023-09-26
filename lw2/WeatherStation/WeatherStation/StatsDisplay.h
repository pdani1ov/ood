#pragma once
#include <iostream>
#include <map>
#include "WeatherData.h"
#include "SensorStat.h"

struct SensorParams
{
	SensorStat temperature;
	SensorStat humidity;
	SensorStat pressure;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		std::cout << "Station name " << observable.GetName() << std::endl;

		if (m_sensors.find(&observable) == m_sensors.end())
		{
			m_sensors.insert(std::make_pair(&observable, SensorParams()));
		}

		SensorParams& params = m_sensors[&observable];

		params.temperature.Update(data.temperature);
		params.humidity.Update(data.humidity);
		params.pressure.Update(data.pressure);

		ShowStatistic("temperature", params.temperature);
		ShowStatistic("humidity", params.humidity);
		ShowStatistic("pressure", params.pressure);
	}

	void ShowStatistic(std::string sensorName, SensorStat const& sensor)
	{
		std::cout << "Max " << sensorName << " " << sensor.GetMaxValue() << std::endl;
		std::cout << "Min " << sensorName << " " << sensor.GetMinValue() << std::endl;
		std::cout << "Average temp " << sensorName << " " << sensor.GetAverage() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	std::map<IObservable<SWeatherInfo>*, SensorParams> m_sensors;
};