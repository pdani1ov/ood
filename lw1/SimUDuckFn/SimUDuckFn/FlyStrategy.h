#pragma once
#include <iostream>
#include <functional>

using FlyStrategy = std::function<void()>;

void FlyNoWay() {}

FlyStrategy MakeFlyWithWings()
{
	unsigned countOfFlights = 0;

	return [countOfFlights]() mutable -> void
	{
		countOfFlights++;
		std::cout << "I'm flying with wings!!" << std::endl;
		std::cout << "Count of flights is " << countOfFlights << std::endl;
	};
}