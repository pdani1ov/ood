#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace multi_with_state
{
	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual std::string ToString()const = 0;
		virtual void AddBalls(unsigned ballsCount) = 0;
		virtual ~IState() = default;
	};

	struct IGumballMachine
	{
		virtual void ReleaseBall() = 0;
		virtual unsigned GetBallCount()const = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;
		virtual bool IncreaseNumberOfQuarters() = 0;
		virtual unsigned GetQuarterCount() = 0;
		virtual void ResetQuarterCount() = 0;
		virtual void RefillBalls(unsigned numBalls) = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "Please wait, we're already giving you a gumball" << std::endl;
		}

		void EjectQuarter() override
		{
			std::cout << "Sorry you already turned the crank" << std::endl;
		}

		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball" << std::endl;
		}

		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
				return;
			}


			if (m_gumballMachine.GetQuarterCount() == 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetHasQuarterState();
			}
		}

		std::string ToString() const override
		{
			return "delivering a gumball";
		}

		void AddBalls(unsigned ballsCount) override
		{
			std::cout << "You add balls: " << std::to_string(ballsCount) << std::endl;
			m_gumballMachine.RefillBalls(ballsCount);
		}

	private:
		IGumballMachine& m_gumballMachine;
	};

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
		}

		void EjectQuarter() override
		{
			if (m_gumballMachine.GetQuarterCount() == 0)
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
			}
			else
			{
				std::cout << "Quarters are ejected" << std::endl;
				m_gumballMachine.ResetQuarterCount();
			}
		}

		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs" << std::endl;
		}

		void Dispense() override
		{
			std::cout << "No gumball dispensed" << std::endl;
		}

		std::string ToString() const override
		{
			return "sold out";
		}

		void AddBalls(unsigned ballsCount) override
		{
			std::cout << "You add balls: " << std::to_string(ballsCount) << std::endl;
			m_gumballMachine.RefillBalls(ballsCount);

			if (m_gumballMachine.GetBallCount() == 0)
			{
				return;
			}

			if (m_gumballMachine.GetQuarterCount() == 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetHasQuarterState();
			}
		}

	private:
		IGumballMachine& m_gumballMachine;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			if (m_gumballMachine.IncreaseNumberOfQuarters())
			{
				std::cout << "You inserted a quarter" << std::endl;
			}
			else
			{
				std::cout << "You can't insert another quarter" << std::endl;
			}
		}

		void EjectQuarter() override
		{
			std::cout << "Quarter returned" << std::endl;
			m_gumballMachine.ResetQuarterCount();
			m_gumballMachine.SetNoQuarterState();
		}

		void TurnCrank() override
		{
			std::cout << "You turned..." << std::endl;
			m_gumballMachine.SetSoldState();
		}

		void Dispense() override
		{
			std::cout << "No gumball dispensed" << std::endl;
		}

		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}

		void AddBalls(unsigned ballsCount) override
		{
			std::cout << "You add balls: " << std::to_string(ballsCount) << std::endl;
			//Переименовать метод SetNumBalls
			m_gumballMachine.RefillBalls(ballsCount);
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You inserted a quarter" << std::endl;
			m_gumballMachine.IncreaseNumberOfQuarters();
			m_gumballMachine.SetHasQuarterState();
		}

		void EjectQuarter() override
		{
			std::cout << "You haven't inserted a quarter" << std::endl;
		}

		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter" << std::endl;
		}

		void Dispense() override
		{
			std::cout << "You need to pay first" << std::endl;
		}

		std::string ToString() const override
		{
			return "waiting for quarter";
		}

		void AddBalls(unsigned ballsCount) override
		{
			std::cout << "You add balls: " << std::to_string(ballsCount) << std::endl;
			m_gumballMachine.RefillBalls(ballsCount);
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CGumballMachine : private IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls = 0)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_state(&m_soldOutState)
			, m_count(numBalls)
		{
			if (m_count > 0)
			{
				m_state = &m_noQuarterState;
			}
		}

		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}

		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}

		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}

		std::string ToString()const
		{
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Quantity of quarters: %3%
Machine is %4%
)");
			return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quarterCount % m_state->ToString()).str();
		}

		void AddBalls(unsigned ballsCount)
		{
			m_state->AddBalls(ballsCount);
		}
	private:
		unsigned GetBallCount() const override
		{
			return m_count;
		}

		virtual void ReleaseBall() override
		{
			if (m_count != 0 && m_quarterCount != 0)
			{
				std::cout << "A gumball comes rolling out the slot..." << std::endl;
				--m_count;
				--m_quarterCount;
			}
		}

		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}

		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}

		void SetSoldState() override
		{
			m_state = &m_soldState;
		}

		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}

		bool IncreaseNumberOfQuarters() override
		{
			if (m_quarterCount == MAX_COUNT_QUARTER)
			{
				return false;
			}
			else
			{
				m_quarterCount++;
				return true;
			}
		}

		unsigned GetQuarterCount() override
		{
			return m_quarterCount;
		}

		void ResetQuarterCount() override
		{
			m_quarterCount = 0;
		}

		void RefillBalls(unsigned numBalls) override
		{
			m_count += numBalls;
		}
	private:
		const unsigned MAX_COUNT_QUARTER = 5;
		const unsigned MIN_COUNT_QUARTER = 0;

		unsigned m_count = 0;
		unsigned m_quarterCount = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;
	};
}