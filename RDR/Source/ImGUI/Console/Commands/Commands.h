#pragma once



struct Command
{
	std::string Description;
	std::string Syntax;
	std::function<bool(std::string _Input)> Handler;
};



class Commands : public Singleton<Commands>
{
	public:
		Commands();
		~Commands();

		void RegisterCommand(const std::string& _Name, const std::string& _Description, const std::string& _Syntax, std::function<bool(std::string _Input)> _Handler);

		void HandleCommand(const std::string& _Input);

		void HelpList();

	private:
		std::unordered_map<std::string, Command> m_Commands;
};