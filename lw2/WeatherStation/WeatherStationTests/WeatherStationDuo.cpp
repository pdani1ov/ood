#include "../../../catch/catch.hpp"
#include "../WeatherStation/WeatherData.h"

class WeatherObserver : public IObserver<SWeatherInfo>
{
public:
	std::string GetStationName() const
	{
		return m_stationName;
	}

	double GetTemperature() const
	{
		return m_temperature;
	}

	double GetHumidity() const
	{
		return m_humidity;
	}

	double GetPressure() const
	{
		return m_pressure;
	}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		m_stationName = observable.GetName();
		m_humidity = data.humidity;
		m_pressure = data.pressure;
		m_temperature = data.temperature;
	}

	std::string m_stationName;
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 0;
};

TEST_CASE("Ñheck operation with multiple stations")
{
	CWeatherData wd1("1");
	CWeatherData wd2("2");

	WeatherObserver observer;

	wd1.RegisterObserver(observer);
	wd2.RegisterObserver(observer);

	wd1.SetMeasurements(10, 20.1, 35);
	REQUIRE(observer.GetStationName() == "1");
	REQUIRE(observer.GetTemperature() == wd1.GetTemperature());
	REQUIRE(observer.GetHumidity() == wd1.GetHumidity());
	REQUIRE(observer.GetPressure() == wd1.GetPressure());

	wd2.SetMeasurements(20, 40.1, 375);
	REQUIRE(observer.GetStationName() == "2");
	REQUIRE(observer.GetTemperature() == wd2.GetTemperature());
	REQUIRE(observer.GetHumidity() == wd2.GetHumidity());
	REQUIRE(observer.GetPressure() == wd2.GetPressure());
}