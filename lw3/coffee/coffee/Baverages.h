#pragma once
#include "IBaverage.h"

// ������� ���������� �������, ��������������� ��� ��������
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription() const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};
