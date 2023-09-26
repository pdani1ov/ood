#pragma once
#include <iostream>
#include "IDanceBehavior.h"

class DanceNoWay : public IDanceBehavior
{
public:
	void Dance() override {}
};