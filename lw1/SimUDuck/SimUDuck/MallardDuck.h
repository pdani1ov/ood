#pragma once
#include <iostream>
#include "Duck.h"
#include "FlyWithWings.h"
#include "QuackBehavior.h"
#include "WaltzBehavior.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(std::make_unique<FlyWithWings>(), 
			std::make_unique<QuackBehavior>(),
			std::make_unique<WaltzBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};