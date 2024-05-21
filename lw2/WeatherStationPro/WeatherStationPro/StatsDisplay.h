#pragma once
#include <iostream>
#include <map>
#include "WeatherInfo.h"
#include "SensorStat.h"
#include "WindStat.h"
#include "Observer.h"

struct SensorParams
{
	SensorStat temperature;
	SensorStat humidity;
	SensorStat pressure;
	WindStat wind;
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
		if (data.windParams)
		{
			params.wind.Update(data.windParams.value().windSpeed, data.windParams.value().windDirection);
		}

		ShowStatistic("temperature", params.temperature);
		ShowStatistic("humidity", params.humidity);
		ShowStatistic("pressure", params.pressure);

		if (data.windParams)
		{
			ShowWindStat(params.wind);
		}
	}

	void ShowStatistic(std::string sensorName, SensorStat const& sensor)
	{
		std::cout << "Max " << sensorName << " " << sensor.GetMaxValue() << std::endl;
		std::cout << "Min " << sensorName << " " << sensor.GetMinValue() << std::endl;
		std::cout << "Average " << sensorName << " " << sensor.GetAverage() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void ShowWindStat(WindStat const& sensor)
	{
		std::cout << "Average wind speed " << sensor.GetAverageSpeed() << std::endl;
		std::cout << "Average wind direction " << sensor.GetAverageDirection() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	std::map<IObservable<SWeatherInfo>*, SensorParams> m_sensors;
};