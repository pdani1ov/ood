#pragma once
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"
#include <cassert>
#include <iostream>

class Duck
{
public:
	Duck(FlyStrategy const& flyStrategy,
		QuackStrategy const& quackStrategy,
		DanceStrategy const& danceStrategy)
		: m_quackStrategy(std::move(quackStrategy)),
		m_danceStrategy(std::move(danceStrategy))
	{
		assert(m_quackStrategy);
		SetFlyBehavior(flyStrategy);
	}

	void Quack() const
	{
		m_quackStrategy();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyStrategy();
	}

	void Dance()
	{
		m_danceStrategy();
	}

	void SetFlyBehavior(FlyStrategy const& flyStrategy)
	{
		assert(flyStrategy);
		m_flyStrategy = flyStrategy;
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;
private:
	FlyStrategy m_flyStrategy;
	QuackStrategy m_quackStrategy;
	DanceStrategy m_danceStrategy;
};