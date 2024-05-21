#pragma once
#include "Baverages.h"

enum class MilkshakeSize
{
	Small,
	Medium, 
	Large
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize size)
		:CBeverage(GetDescription(size))
	{
		SetCost(size);
	}

	double GetCost() const override
	{
		return m_cost;
	}
private:
	//Выбрать имя поудачливее
	void SetCost(MilkshakeSize size)
	{
		switch (size)
		{
		case MilkshakeSize::Small:
			m_cost = 50;
			break;
		case MilkshakeSize::Medium:
			m_cost = 60;
			break;
		case MilkshakeSize::Large:
			m_cost = 80;
			break;
		}
	}

	std::string GetDescription(MilkshakeSize size)
	{
		std::string description;

		switch (size)
		{
		case MilkshakeSize::Small:
			description = "Small";
			break;
		case MilkshakeSize::Medium:
			description = "Medium";
			break;
		case MilkshakeSize::Large:
			description = "Large";
			break;
		}

		description += " milkshake";

		return description;
	}

	unsigned m_cost;
};