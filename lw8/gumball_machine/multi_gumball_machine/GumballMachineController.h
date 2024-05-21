#pragma once
#include "CMenu.h"
#include "MultiGumballMachineWithState.h"
#include <optional>

class CGumballMachineController
{
public:
	CGumballMachineController()
		:m_machine(std::make_unique<multi_with_state::CGumballMachine>())
	{
		auto ejectQuarter = [this](std::istream&) { this->EjectQuarter(); };
		auto insertQuarter = [this](std::istream&) { this->InsertQuarter(); };
		auto turnCrank = [this](std::istream&) { this->TurnCrank(); };
		auto toString = [this](std::istream&) { this->ToString(); };
		auto addBalls = [this](std::istream& in) { this->AddBalls(in); };
		auto help = [this](std::istream&) { m_menu.ShowInstructions(); };
		auto exit = [this](std::istream&) { m_menu.Exit(); };

		m_menu.AddItem("help", "Help", help);
		m_menu.AddItem("exit", "Exit", exit);
		m_menu.AddItem("ejectQuarter", "Eject quarter.", ejectQuarter);
		m_menu.AddItem("insertQuarter", "Insert quarter.", insertQuarter);
		m_menu.AddItem("turnCrank", "Turn crank.", turnCrank);
		m_menu.AddItem("showInfo", "ShowMachineInfo", toString);
		m_menu.AddItem("addBalls", "Add gumballs in machine. Args: <quantity of gumballs>", addBalls);
	}

	void Run()
	{
		m_menu.Run();
	}
private:
	void EjectQuarter()
	{
		m_machine->EjectQuarter();
	}

	void InsertQuarter()
	{
		m_machine->InsertQuarter();
	}

	void TurnCrank()
	{
		m_machine->TurnCrank();
	}

	void ToString() const
	{
		std::cout << m_machine->ToString() << std::endl;
	}

	void AddBalls(std::istream& in)
	{
		std::string quantityStr;

		in >> quantityStr;

		if (quantityStr.size() == 0)
		{
			throw std::invalid_argument("Add balls: invalid argument");
		}

		std::optional<int> quantity = StringToNum(quantityStr);

		if (quantity == std::nullopt)
		{
			throw std::invalid_argument("Add balls: invalid argument");
		}

		if (quantity.value() < 0)
		{
			throw std::invalid_argument("Add balls: invalid argument");
		}

		m_machine->AddBalls(quantity.value());
	}

	std::optional<int> StringToNum(std::string& str) const
	{
		try
		{
			int num = std::stoi(str);
			return num;
		}
		catch (...)
		{
			return std::nullopt;
		}
	}

	CMenu m_menu;
	std::unique_ptr<multi_with_state::CGumballMachine> m_machine;
};