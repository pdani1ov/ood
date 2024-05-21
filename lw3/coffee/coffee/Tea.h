#pragma once
#include "Baverages.h"

enum class TeaType
{
	Black,
	Green,
	Oolong,
	Matcha
};

// ×àé
class CTea : public CBeverage
{
public:
	CTea(TeaType type)
		:CBeverage(GetDescription(type))
	{}

	double GetCost() const override
	{
		return 30;
	}
private:
	std::string GetDescription(TeaType type)
	{
		std::string desription;

		switch (type)
		{
		case TeaType::Black:
			desription = "Black";
			break;
		case TeaType::Green:
			desription = "Green";
			break;
		case TeaType::Matcha:
			desription = "Matcha";
			break;
		case TeaType::Oolong:
			desription = "Oolong";
			break;
		}

		desription += " tea";

		return desription;
	}
};