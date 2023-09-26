#pragma once
#include <iostream>
#include "Duck.h"
#include "FlyNoWay.h"
#include "QuackBehavior.h"
#include "DanceNoWay.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(std::make_unique<FlyNoWay>(), 
			std::make_unique<QuackBehavior>(),
			std::make_unique<DanceNoWay>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};