#include "printStatement.h"


PrintStatement::PrintStatement(std::string argument, std::map<std::string, int>& variables)
{
	std::size_t quotesStart = argument.find('\"');
	if (quotesStart == std::string::npos)
	{
		isStringLiteral = false;
		std::string command = "PRINT ";
		std::size_t commandLocation = argument.find(command) + (unsigned)command.length();
		value = argument.substr(commandLocation, (unsigned)argument.length() - commandLocation);
	}
	else
	{
		isStringLiteral = true;
		quotesStart++;
		std::size_t quotesEnd = argument.find('\"', quotesStart);
		if (quotesEnd == std::string::npos)
		{
			value = "Missing quotes";
		}
		else
		{
			value = argument.substr(quotesStart, quotesEnd - quotesStart);
		}
	}
}

PrintStatement::~PrintStatement()
{

}

bool PrintStatement::Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	if (isStringLiteral)
	{
		std::cout << value << std::endl;
	}
	else
	{
		std::map<std::string, int>::iterator toPrint = variables.find(value);
		if (toPrint == variables.end())
		{
			std::cerr << value << " does not exist" << std::endl;
			throw ExceptionRuntimeError();
			return false;
		}

		std::cout << toPrint->second << std::endl;
	}
	iterator++;
	return true;
}