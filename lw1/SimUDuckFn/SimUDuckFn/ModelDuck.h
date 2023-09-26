#pragma once
#include "Duck.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay,
			SayQuack,
			DanceNoWay)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};