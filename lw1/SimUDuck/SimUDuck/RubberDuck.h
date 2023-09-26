#pragma once
#include <iostream>
#include "Duck.h"
#include "FlyNoWay.h"
#include "SqueakBehavior.h"
#include "DanceNoWay.h"

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(std::make_unique<FlyNoWay>(), 
			std::make_unique<SqueakBehavior>(),
			std::make_unique<DanceNoWay>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};