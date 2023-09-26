#pragma once
#include <iostream>
#include <functional>

using QuackStrategy = std::function<void()>;

void SayQuack() 
{
	std::cout << "Quack Quack!!!" << std::endl;
}

void Squeak()
{
	std::cout << "Squeek!!!" << std::endl;
}

void MuteQuack() {}