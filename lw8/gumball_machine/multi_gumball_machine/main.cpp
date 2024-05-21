﻿#include "MultiGumballMachineWithState.h"
#include "NaiveMultiGumBallMachine.h"
#include "GumballMachineController.h"
using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType& m)
{
	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.EjectQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;
}

void TestNaiveGumballMachine()
{
	multi_naive::CGumballMachine m(5);
	TestGumballMachine(m);
}

void TestGumballMachineWithState()
{
	multi_with_state::CGumballMachine m(5);
	TestGumballMachine(m);
}

int main()
{


	TestNaiveGumballMachine();

	cout << "\n-----------------\n";
	TestGumballMachineWithState();
	cout << "\n-----------------\n";

	CGumballMachineController controller;
	controller.Run();

	return 0;
}
