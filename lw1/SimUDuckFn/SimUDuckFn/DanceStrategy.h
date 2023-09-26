#pragma once
#include <iostream>
#include <functional>

using DanceStrategy = std::function<void()>;

void DanceMinuet()
{
	std::cout << "I'm dancing minuet!!!" << std::endl;
}

void DanceWaltz()
{
	std::cout << "I'm dancing waltz!!!" << std::endl;
}

void DanceNoWay() {}