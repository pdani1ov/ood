#pragma once
#include "IBaverage.h"

// Ѕазовый декоратор "ƒобавка к напитку". “акже €вл€етс€ напитком
class CCondimentDecorator : public IBeverage
{
public:
	std::string GetDescription()const override
	{
		// ќписание декорированного напитка добавл€етс€ к описанию оборачиваемого напитка
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost()const override
	{
		// —тоимость складываетс€ из стоимости добавки и стоимости декорируемого напитка
		return m_beverage->GetCost() + GetCondimentCost();
	}

	// —тоимость и описание добавки вычисл€етс€ в классах конкретных декораторов
	virtual std::string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;
protected:
	CCondimentDecorator(IBeveragePtr&& beverage)
		: m_beverage(move(beverage))
	{
	}
private:
	IBeveragePtr m_beverage;
};