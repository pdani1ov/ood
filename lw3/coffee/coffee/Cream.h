#pragma once
#include "Condiments.h"

class CCream : public CCondimentDecorator {
public:
	CCream(IBeveragePtr&& beverage)
		: CCondimentDecorator(move(beverage))
	{}
protected:
	double GetCondimentCost()const override
	{
		// Чем больше кубиков, тем больше стоимость.
		// Сухой лед стоит дороже
		return 25;
	}

	std::string GetCondimentDescription()const override
	{
		return "Cream";
	}
};