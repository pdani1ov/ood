#pragma once
#include "Condiments.h"

// ��������� �������
class CCoconutFlakes : public CCondimentDecorator
{
public:
	CCoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
		: CCondimentDecorator(move(beverage))
		, m_mass(mass)
	{}

protected:
	double GetCondimentCost()const override
	{
		return 1.0 * m_mass;
	}
	std::string GetCondimentDescription()const override
	{
		return "Coconut flakes " + std::to_string(m_mass) + "g";
	}
private:
	unsigned m_mass;
};