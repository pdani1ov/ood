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

class CStatsDisplay : public IObserver<SWeatherInfo, WeatherParameter>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo, WeatherParameter>& observable, std::set<WeatherParameter> params) override
	{
		std::cout << "Station name " << observable.GetName() << std::endl;

		if (m_sensors.find(&observable) == m_sensors.end())
		{
			m_sensors.insert(std::make_pair(&observable, SensorParams()));
		}

		SensorParams& stats = m_sensors[&observable];

		UpdatedParams(data, params, stats);

		ShowAllStatistics(params, stats);
	}

	void UpdatedParams(SWeatherInfo const& data, std::set<WeatherParameter> params, SensorParams& sensorParams)
	{
		if (params.contains(WeatherParameter::Temperature)) {
			sensorParams.temperature.Update(data.temperature);
		}
		if (params.contains(WeatherParameter::Humidity)) {
			sensorParams.humidity.Update(data.humidity);
		}
		if (params.contains(WeatherParameter::Pressure)) {
			sensorParams.pressure.Update(data.pressure);
		}
		if (params.contains(WeatherParameter::Wind)) {
			sensorParams.wind.Update(data.windSpeed, data.windDirection);
		}
	}

	void ShowAllStatistics(std::set<WeatherParameter> params, SensorParams& sensorParams)
	{
		if (params.contains(WeatherParameter::Temperature)) {
			ShowStat("temperature", sensorParams.temperature);
		}
		if (params.contains(WeatherParameter::Humidity)) {
			ShowStat("humidity", sensorParams.humidity);
		}
		if (params.contains(WeatherParameter::Pressure)) {
			ShowStat("pressure", sensorParams.pressure);
		}
		if (params.contains(WeatherParameter::Wind)) {
			ShowWindStat(sensorParams.wind);
		}
	}

	void ShowStat(std::string sensorName, SensorStat const& sensor)
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

	std::map<IObservable<SWeatherInfo, WeatherParameter>*, SensorParams> m_sensors;
};