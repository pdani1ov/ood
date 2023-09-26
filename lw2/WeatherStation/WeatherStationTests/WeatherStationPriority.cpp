#include "../../../catch/catch.hpp"
#include "../WeatherStation/Observer.h"

class Observer: public IObserver<std::string>
{
public:
	Observer(std::string* str, unsigned priority)
		:m_str(str),
		m_priority(priority)
	{}

	void Update(std::string const& data, IObservable<std::string>& observable) override
	{
		*m_str += std::to_string(m_priority);
	}
private:
	std::string* m_str;
	unsigned m_priority;
};

class Observable : public CObservable<std::string>
{
protected:
	std::string GetChangedData() const override
	{
		return "";
	}

	std::string GetName() override
	{
		return "";
	}
};

TEST_CASE("DS")
{
	REQUIRE(true);
}

TEST_CASE("Check observers alert by priority")
{
	std::string str = "";

	Observable observable;

	Observer observer1(&str, 1);
	Observer observer2(&str, 2);
	Observer observer3(&str, 3);
	observable.RegisterObserver(observer1, 1);
	observable.RegisterObserver(observer2, 2);
	observable.RegisterObserver(observer3, 3);

	observable.NotifyObservers();
	REQUIRE(str == "321");
}

TEST_CASE("Ñheck notification of observers with the same priority")
{
	std::string str = "";

	Observable observable;

	Observer observer1(&str, 1);
	Observer observer2(&str, 1);
	Observer observer3(&str, 1);
	observable.RegisterObserver(observer1, 1);
	observable.RegisterObserver(observer2, 1);
	observable.RegisterObserver(observer3, 1);

	observable.NotifyObservers();
	REQUIRE(str == "111");
}