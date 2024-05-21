#pragma once
#include "Condiments.h"

enum class IceCubeType
{
	Dry,	// ����� ��� (��� ������� ��������� �������)
	Water	// ������� ������ �� ����
};

// ������� "������ ����". ������������ ����� � ����������� �������, ��� ������ �� ���������
// � ��������
class CIceCubes : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
		: CCondimentDecorator(move(beverage))
		, m_quantity(quantity)
		, m_type(type)
	{}
protected:
	double GetCondimentCost()const override
	{
		// ��� ������ �������, ��� ������ ���������.
		// ����� ��� ����� ������
		return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
	}
	std::string GetCondimentDescription()const override
	{
		return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
			+ " ice cubes x " + std::to_string(m_quantity);
	}
private:
	unsigned m_quantity;
	IceCubeType m_type;
};