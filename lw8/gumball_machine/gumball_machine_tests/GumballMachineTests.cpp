#include "../../../catch/catch.hpp"
#include "../gumball_machine/GumBallMachineWithState.h"
#include "../gumball_machine/GumBallMachineWithDynamicallyCreatedState.h"
#include "../gumball_machine/NaiveGumBallMachine.h"

const unsigned GUMBALL_COUNT = 2;

const std::string NO_QUARTER_STATE_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 2 gumballs
Machine is waiting for quarter
)";

const std::string HAS_QUARTER_STATE_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 2 gumballs
Machine is waiting for turn of crank
)";

const std::string NO_QUARTER_STATE_WITH_ONE_BALL_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 1 gumball
Machine is waiting for quarter
)";

const std::string SOLDOUT_STATE_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 0 gumballs
Machine is sold out
)";

const std::string NO_QUARTER_ENUM_STATE_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 2 gumballs
Machine is waiting for quarter
)";

const std::string HAS_QUARTER_ENUM_STATE_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 2 gumballs
Machine is waiting for turn of crank
)";

const std::string NO_QUARTER_ENUM_STATE_WITH_ONE_BALL_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 1 gumball
Machine is waiting for quarter
)";

const std::string SOLDOUT_ENUM_STATE_TEXT = R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 0 gumballs
Machine is sold out
)";

TEST_CASE("Gumball machine work")
{
	with_state::CGumballMachine machine(GUMBALL_COUNT);

	REQUIRE(machine.ToString() == NO_QUARTER_STATE_TEXT);
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());

	machine.InsertQuarter();
	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE(machine.ToString() == HAS_QUARTER_STATE_TEXT);
	machine.EjectQuarter();
	REQUIRE(machine.ToString() == NO_QUARTER_STATE_TEXT);

	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == NO_QUARTER_STATE_WITH_ONE_BALL_TEXT);

	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == SOLDOUT_STATE_TEXT);
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());
}

TEST_CASE("Naive gumball machine work")
{
	naive::CGumballMachine machine(GUMBALL_COUNT);

	REQUIRE(machine.ToString() == NO_QUARTER_ENUM_STATE_TEXT);
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());

	machine.InsertQuarter();
	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE(machine.ToString() == HAS_QUARTER_ENUM_STATE_TEXT);
	machine.EjectQuarter();
	REQUIRE(machine.ToString() == NO_QUARTER_ENUM_STATE_TEXT);

	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == NO_QUARTER_ENUM_STATE_WITH_ONE_BALL_TEXT);

	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == SOLDOUT_ENUM_STATE_TEXT);
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());
}

TEST_CASE("Gumball machine with dynamically work")
{
	with_dynamic_state::CGumballMachine machine(GUMBALL_COUNT);

	REQUIRE(machine.ToString() == NO_QUARTER_STATE_TEXT);
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());

	machine.InsertQuarter();
	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE(machine.ToString() == HAS_QUARTER_STATE_TEXT);
	machine.EjectQuarter();
	REQUIRE(machine.ToString() == NO_QUARTER_STATE_TEXT);

	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == NO_QUARTER_STATE_WITH_ONE_BALL_TEXT);

	machine.InsertQuarter();
	machine.TurnCrank();
	REQUIRE(machine.ToString() == SOLDOUT_STATE_TEXT);
	REQUIRE_NOTHROW(machine.EjectQuarter());
	REQUIRE_NOTHROW(machine.InsertQuarter());
	REQUIRE_NOTHROW(machine.TurnCrank());
}