#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace multi_naive
{
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,
			NoQuarter,
			HasQuarter,
			Sold,
		};

		CGumballMachine(unsigned count)
			: m_count(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		{}

		void InsertQuarter()
		{
			switch (m_state)
			{
			case State::SoldOut:
				std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
				break;
			case State::NoQuarter:
				std::cout << "You inserted a quarter" << std::endl;
				m_quarterCount++;
				m_state = State::HasQuarter;
				break;
			case State::HasQuarter:
				if (m_quarterCount == MAX_QUARTER_COUNT)
				{
					std::cout << "You can't insert another quarter" << std::endl;
				}
				else
				{
					m_quarterCount++;
					std::cout << "You inserted a quarter" << std::endl;
				}
				break;
			case State::Sold:
				std::cout << "Please wait, we're already giving you a gumball" << std::endl;
				break;
			}
		}

		void EjectQuarter()
		{
			switch (m_state)
			{
			case State::HasQuarter:
				std::cout << "Quarter returned" << std::endl;
				m_quarterCount = 0;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				std::cout << "You haven't inserted a quarter" << std::endl;
				break;
			case State::Sold:
				std::cout << "Sorry you already turned the crank" << std::endl;
				break;
			case State::SoldOut:
				if (m_quarterCount == 0)
				{
					std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
				}
				else
				{
					std::cout << "Quarter returned" << std::endl;
					m_quarterCount = 0;
				}
				break;
			}
		}

		void TurnCrank()
		{
			switch (m_state)
			{
			case State::SoldOut:
				std::cout << "You turned but there's no gumballs" << std::endl;
				break;
			case State::NoQuarter:
				std::cout << "You turned but there's no quarter" << std::endl;
				break;
			case State::HasQuarter:
				std::cout << "You turned..." << std::endl;
				m_state = State::Sold;
				Dispense();
				break;
			case State::Sold:
				std::cout << "Turning twice doesn't get you another gumball" << std::endl;
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
Quantity of quarters: %3%
Machine is %4%
)");
			return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quarterCount % state).str();
		}

		void AddBalls(unsigned numBalls)
		{
			switch (m_state)
			{
			case State::HasQuarter:
				std::cout << "You add balls: " << std::to_string(numBalls) << std::endl;
				m_count += numBalls;
				break;
			case State::NoQuarter:
				std::cout << "You add balls: " << std::to_string(numBalls) << std::endl;
				m_count += numBalls;
				break;
			case State::Sold:
				std::cout << "You add balls: " << std::to_string(numBalls) << std::endl;
				m_count += numBalls;
				break;
			case State::SoldOut:
				std::cout << "You add balls: " << std::to_string(numBalls) << std::endl;
				m_count = numBalls;
				if (m_count != MIN_QUARTER_COUNT && m_quarterCount != MIN_QUARTER_COUNT)
				{
					m_state = State::HasQuarter;
				} 
				else if (m_count != MIN_QUARTER_COUNT)
				{
					m_state = State::NoQuarter;
				}
				break;
			}
		}
	private:
		void ReleaseBall()
		{
			if (m_count != MIN_QUARTER_COUNT && m_quarterCount != MIN_QUARTER_COUNT)
			{
				std::cout << "A gumball comes rolling out the slot..." << std::endl;
				--m_count;
				--m_quarterCount;
			}
		}

		void Dispense()
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				cout << "A gumball comes rolling out the slot\n";
				ReleaseBall();
				if (m_count == 0)
				{
					cout << "Oops, out of gumballs\n";
					m_state = State::SoldOut;
				}
				else
				{
					m_state = m_quarterCount > 0 ? State::HasQuarter : State::NoQuarter;
				}
				break;
			case State::NoQuarter:
				cout << "You need to pay first\n";
				break;
			case State::SoldOut:
			case State::HasQuarter:
				cout << "No gumball dispensed\n";
				break;
			}
		}

		const unsigned MAX_QUARTER_COUNT = 5;
		const unsigned MIN_QUARTER_COUNT = 0;

		unsigned m_count;
		unsigned m_quarterCount = 0;
		State m_state = State::SoldOut;
	};
}