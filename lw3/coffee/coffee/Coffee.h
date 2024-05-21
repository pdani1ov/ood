#pragma once
#include "Baverages.h"

enum class CoffeeSize
{
	Standart,
	Double
};

// ����
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// ���������
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeSize type)
		:CCoffee(GetDescription(type))
	{
		SetCost(type);
	}

	double GetCost() const override
	{
		return m_cost;
	}
private:
	//������������� � ���-�� �������
	void SetCost(CoffeeSize type)
	{
		switch (type)
		{
		case CoffeeSize::Standart:
			m_cost = 80;
			break;
		case CoffeeSize::Double:
			m_cost = 120;
			break;
		}
	}

	std::string GetDescription(CoffeeSize type)
	{
		std::string description;

		switch (type)
		{
		case CoffeeSize::Standart:
			description = "Cappuccino";
			break;
		case CoffeeSize::Double:
			description = "Double cappuccino";
			break;
		}

		return description;
	}

	unsigned m_cost;
};

// �����
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeSize type)
		:CCoffee(GetDescription(type))
	{
		SetCost(type);
	}

	double GetCost() const override
	{
		return 90;
	}
private:
	void SetCost(CoffeeSize type)
	{
		switch (type)
		{
		case CoffeeSize::Standart:
			m_cost = 90;
			break;
		case CoffeeSize::Double:
			m_cost = 130;
			break;
		}
	}

	std::string GetDescription(CoffeeSize type)
	{
		std::string description;

		switch (type)
		{
		case CoffeeSize::Standart:
			description = "Latte";
			break;
		case CoffeeSize::Double:
			description = "Double latte";
			break;
		}

		return description;
	}

	unsigned m_cost;
};