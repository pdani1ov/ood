#pragma once
#include <iostream>
#include "Observer.h"
#include "WeatherInfo.h"

class CWeatherDataPro : public CObservable<SWeatherInfo, WeatherParameter>
{
public:

	CWeatherDataPro(std::string stationName)
		:m_stationName(stationName)
	{}

	// ����������� � �������� �������
	double GetTemperature() const
	{
		return m_temperature;
	}
	// ������������� ��������� (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// ����������� �������� (� ��.��.��)
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindDirection() const
	{
		return m_windDirection;
	}

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	void MeasurementsChanged(std::set<WeatherParameter> params)
	{
		NotifyObservers(params);
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		std::set<WeatherParameter> updatedParams;
		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			updatedParams.insert(WeatherParameter::Humidity);
		}
		if (m_temperature != temp)
		{
			m_temperature = temp;
			updatedParams.insert(WeatherParameter::Temperature);
		}
		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			updatedParams.insert(WeatherParameter::Pressure);
		}
		if (m_windSpeed != windSpeed || m_windDirection != windDirection) {
			m_windSpeed = windSpeed;
			m_windDirection = windDirection;
			updatedParams.insert(WeatherParameter::Wind);
		}

		MeasurementsChanged(updatedParams);
	}

	std::string GetName() override
	{
		return m_stationName;
	}
protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windDirection = GetWindDirection();
		info.windSpeed = GetWindSpeed();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windDirection = 0.0;
	double m_windSpeed = 0.0;
	std::string m_stationName;
};