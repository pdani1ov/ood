#pragma once
#include <iostream>
#include "Condiments.h"

class CChocolate : public CCondimentDecorator
{
public:
	CChocolate(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CCondimentDecorator(move(beverage))
	{
		if (quantity > 5)
		{
			//Выбрасывать исключение 
			throw std::exception("You cannot add more than 5 pieces of chocolate.");
		}
		else 
		{
			m_quantity = quantity;
		}
	}
protected:
	double GetCondimentCost() const override
	{
		return 10.0 * m_quantity;
	}

	std::string GetCondimentDescription()const override
	{
		return "Chocolate pieces x" + std::to_string(m_quantity);
	}
private:
	unsigned m_quantity;
};