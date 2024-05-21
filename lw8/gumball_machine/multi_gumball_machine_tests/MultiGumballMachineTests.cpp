#include "../../../catch/catch.hpp"
#include "../multi_gumball_machine/MultiGumballMachineWithState.h"
#include "../multi_gumball_machine/NaiveMultiGumBallMachine.h"
#include <boost/format.hpp>

enum class StateMachine
{
	HasQuarter,
	NoQuarter,
	SoldOut,
};

std::string GetInfoForMachine(unsigned numOfBalls, unsigned numOfQuarters, StateMachine state, bool withState)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016%1%
Inventory: %2% gumball%3%
Quantity of quarters: %4%
Machine is %5%
)");

	std::string stateMsg;

	switch (state)
	{
	case StateMachine::HasQuarter:
		stateMsg = "waiting for turn of crank";
		break;
	case StateMachine::NoQuarter:
		stateMsg = "waiting for quarter";
		break;
	case StateMachine::SoldOut:
		stateMsg = "sold out";
		break;
	}

	return (fmt % (withState ? " (with state)" : "") % numOfBalls % (numOfBalls != 1 ? "s" : "") % numOfQuarters % stateMsg).str();
};

TEST_CASE("Multi gumball machine work")
{
	multi_with_state::CGumballMachine machine(2);
	REQUIRE(machine.ToString() == GetInfoForMachine(2, 0, StateMachine::NoQuarter, true));
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());

	for (unsigned i = 1; i <= 5; i++)
	{
		machine.InsertQuarter();
		std::string resultInfo = GetInfoForMachine(2, i, StateMachine::HasQuarter, true); 
		REQUIRE(machine.ToString() == resultInfo);
	}
	machine.InsertQuarter();
	REQUIRE(machine.ToString() == GetInfoForMachine(2, 5, StateMachine::HasQuarter, true));

	machine.TurnCrank();
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 4, StateMachine::HasQuarter, true));

	machine.EjectQuarter();
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 0, StateMachine::NoQuarter, true));

	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == GetInfoForMachine(0, 1, StateMachine::SoldOut, true));

	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE(machine.ToString() == GetInfoForMachine(0, 0, StateMachine::SoldOut, true));

	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());
}

TEST_CASE("Multi naive gumball machine work")
{
	multi_naive::CGumballMachine machine(2);
	REQUIRE(machine.ToString() == GetInfoForMachine(2, 0, StateMachine::NoQuarter, false));
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());

	for (unsigned i = 1; i <= 5; i++)
	{
		machine.InsertQuarter();
		std::string resultInfo = GetInfoForMachine(2, i, StateMachine::HasQuarter, false);
		REQUIRE(machine.ToString() == resultInfo);
	}
	machine.InsertQuarter();
	REQUIRE(machine.ToString() == GetInfoForMachine(2, 5, StateMachine::HasQuarter, false));

	machine.TurnCrank();
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 4, StateMachine::HasQuarter, false));

	machine.EjectQuarter();
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 0, StateMachine::NoQuarter, false));

	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == GetInfoForMachine(0, 1, StateMachine::SoldOut, false));

	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE(machine.ToString() == GetInfoForMachine(0, 0, StateMachine::SoldOut, false));

	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());
}

TEST_CASE("Multi gumball machine: add balls")
{
	multi_with_state::CGumballMachine machine(1);
	machine.AddBalls(1);

	REQUIRE(machine.ToString() == GetInfoForMachine(2, 0, StateMachine::NoQuarter, true));

	machine.InsertQuarter();
	machine.AddBalls(1);
	REQUIRE(machine.ToString() == GetInfoForMachine(3, 1, StateMachine::HasQuarter, true));

	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.TurnCrank();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == GetInfoForMachine(0, 0, StateMachine::SoldOut, true));

	machine.AddBalls(1);
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 0, StateMachine::NoQuarter, true));

	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.AddBalls(0);
	machine.AddBalls(1);
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 1, StateMachine::HasQuarter, true));
}

TEST_CASE("Naive multi gumball machine: add balls")
{
	multi_naive::CGumballMachine machine(1);
	machine.AddBalls(1);

	REQUIRE(machine.ToString() == GetInfoForMachine(2, 0, StateMachine::NoQuarter, false));

	machine.InsertQuarter();
	machine.AddBalls(1);
	REQUIRE(machine.ToString() == GetInfoForMachine(3, 1, StateMachine::HasQuarter, false));

	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.TurnCrank();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == GetInfoForMachine(0, 0, StateMachine::SoldOut, false));

	machine.AddBalls(1);
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 0, StateMachine::NoQuarter, false));

	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.AddBalls(0);
	machine.AddBalls(1);
	REQUIRE(machine.ToString() == GetInfoForMachine(1, 1, StateMachine::HasQuarter, false));
}

//Уменьшить дублирование кода в тестах(например, реализовать функциюю)