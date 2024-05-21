#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

class CMenu
{
public:
	using Command = std::function<void(std::istream& args)>;

	void AddItem(const std::string& shortcut, const std::string& description, const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run()
	{
		std::string command;
		while (!m_exit && std::getline(std::cin, command)
			&& ExecuteCommand(command))
		{
		}
	}

	void ShowInstructions() const
	{
		std::cout << "Commands list:\n";
		for (auto& item : m_items)
		{
			std::cout << "  " << item.shortcut << ": " << item.description << std::endl;
		}
	}

	void Exit()
	{
		m_exit = true;
	}
private:
	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut), description(description), command(command)
		{}

		std::string shortcut;
		std::string description;
		Command command;
	};

	bool ExecuteCommand(const std::string& command)
	{
		auto toLower = [](char ch) {
			return std::tolower(ch);
		};

		m_exit = false;

		std::stringstream ss(command);
		std::string commandName;
		ss >> commandName;

		auto checkShortcut = [commandName](Item& item) {
			return commandName == item.shortcut;
		};

		std::transform(commandName.begin(), commandName.end(), commandName.begin(), toLower);

		auto it = std::find_if(m_items.begin(), m_items.end(), checkShortcut);

		if (it != m_items.end())
		{
			try
			{
				it->command(ss);
			}
			catch (std::exception const& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}

		return !m_exit;
	}

	std::vector<Item> m_items;
	bool m_exit = false;
};