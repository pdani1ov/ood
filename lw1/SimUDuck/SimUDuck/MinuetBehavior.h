#pragma once
#include <iostream>
#include "IDanceBehavior.h"

class MinuetBehavior : public IDanceBehavior 
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing minuet!!!" << std::endl;
	}
};