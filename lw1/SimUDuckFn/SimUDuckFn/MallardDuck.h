#pragma once
#include "Duck.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(MakeFlyWithWings(),
			SayQuack,
			DanceWaltz)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};