#pragma once
#include "Condiments.h"

enum class LiquorType
{
	Chocolate,
	Nut
};

class CLiquor : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr&& beverage, LiquorType type)
		: CCondimentDecorator(move(beverage)),
		m_liquorType(type)
	{}
protected:
	double GetCondimentCost()const override
	{
		return 50;
	}

	std::string GetCondimentDescription()const override
	{
		std::string description;

		switch (m_liquorType)
		{
		case LiquorType::Chocolate:
			description = "Chocolate liquor";
			break;
		case LiquorType::Nut:
			description = "Nut liquor";
			break;
		}

		return description;
	}

private:
	LiquorType m_liquorType;
};