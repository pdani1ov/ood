#pragma once

#include <iostream>
#include <boost/format.hpp>

namespace naive
{
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,		// Жвачка закончилась
			NoQuarter,		// Нет монетки
			HasQuarter,		// Есть монетка
			Sold,			// Монетка выдана
		};

		CGumballMachine(unsigned count)
			: m_count(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		{
		}

		void InsertQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You can't insert a quarter, the machine is sold out" << endl;
				break;
			case State::NoQuarter:
				cout << "You inserted a quarter" << endl;
				m_state = State::HasQuarter;
				break;
			case State::HasQuarter:
				cout << "You can't insert another quarter" << endl;
				break;
			case State::Sold:
				cout << "Please wait, we're already giving you a gumball" << endl;
				break;
			}
		}

		void EjectQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::HasQuarter:
				cout << "Quarter returned" << endl;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				cout << "You haven't inserted a quarter" << endl;
				break;
			case State::Sold:
				cout << "Sorry you already turned the crank" << endl;
				break;
			case State::SoldOut:
				cout << "You can't eject, you haven't inserted a quarter yet" << endl;
				break;
			}
		}

		void TurnCrank()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You turned but there's no gumballs" << endl;
				break;
			case State::NoQuarter:
				cout << "You turned but there's no quarter" << endl;
				break;
			case State::HasQuarter:
				cout << "You turned..." << endl;
				m_state = State::Sold;
				Dispense();
				break;
			case State::Sold:
				cout << "Turning twice doesn't get you another gumball" << endl;
				break;
			}
		}

		std::string ToString()const
		{
			std::string state =
				(m_state == State::SoldOut) ? "sold out" :
				(m_state == State::NoQuarter) ? "waiting for quarter" :
				(m_state == State::HasQuarter) ? "waiting for turn of crank"
				: "delivering a gumball";
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");
			return (fmt % m_count % (m_count != 1 ? "s" : "") % state).str();
		}

	private:
		void Dispense()
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				cout << "A gumball comes rolling out the slot" << endl;
				--m_count;
				if (m_count == 0)
				{
					cout << "Oops, out of gumballs" << endl;
					m_state = State::SoldOut;
				}
				else
				{
					m_state = State::NoQuarter;
				}
				break;
			case State::NoQuarter:
				cout << "You need to pay first" << endl;
				break;
			case State::SoldOut:
			case State::HasQuarter:
				cout << "No gumball dispensed" << endl;
				break;
			}
		}

		unsigned m_count;	// Количество шариков
		State m_state = State::SoldOut;
	};
}