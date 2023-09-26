#pragma once
#include <iostream>
#include "IFlyBehavior.h"

class FlyWithWings : public IFlyBehavior {
public:
	void Fly() override {
		m_countOfFlights++;
		std::cout << "I'm flying with wings!!" << std::endl;
		std::cout << "Count of flights: " << m_countOfFlights << std::endl;
	}
private:
	unsigned m_countOfFlights;
};