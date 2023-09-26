#pragma once
#include <iostream>
#include "Duck.h"
#include "FlyWithWings.h"
#include "QuackBehavior.h"
#include "MinuetBehavior.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(std::make_unique<FlyWithWings>(), 
			std::make_unique<QuackBehavior>(),
			std::make_unique<MinuetBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};