#include "pch.h"



Commands::Commands()
{
	m_Commands = {};

	RegisterCommand("help", "List of all available commands.", "", [=](std::string _input)
	{
		HelpList();

		return true;
	});

	RegisterCommand("quit", "Force close the game.", "", [](std::string _input)
	{
		ExitProcess(EXIT_SUCCESS);

		return true;
	});

	RegisterCommand("exit", "Alias of 'quit' command.", "", [](std::string _input)
	{
		ExitProcess(EXIT_SUCCESS);

		return true;
	});
}



Commands::~Commands()
{
	m_Commands.clear();
}



void Commands::RegisterCommand(const std::string& _Name, const std::string& _Description, const std::string& _Syntax, std::function<bool(std::string _input)> _Handler)
{
	Command cmd;
	cmd.Description = _Description;
	cmd.Syntax = _Syntax;
	cmd.Handler = _Handler;

	m_Commands.emplace(_Name, cmd);
}



void Commands::HandleCommand(const std::string& _Input)
{
	std::string command_name = _Input;

	size_t index = _Input.find(' ');

	if (index != std::string::npos)
	{
		command_name = _Input.substr(0, index);
	}

	if (m_Commands.contains(command_name))
	{
		const auto& command = m_Commands.at(command_name);

		std::string args;

		if (index != std::string::npos)
		{
			args = _Input.substr(index + 1, _Input.size() - index);
		}

		bool success = command.Handler(args);

		if (!success)
		{
			Log::AddToCache(Log_ConsoleOnly, "Incorrect command syntax, type 'help' to check the syntax");
		}
	}
	else
	{
		Log::AddToCache(Log_ConsoleOnly, "No such command found, type 'help' to get all commands list");
	}
}



void Commands::HelpList()
{
	for (const auto& [name, command] : m_Commands)
	{
		Log::AddToCache(Log_ConsoleOnly, "%s %s\n%s", name.c_str(), command.Syntax.c_str(), command.Description.c_str());
	}
}